
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct GameVertInput {
    float p[3];
    float n[3];
    float u[2];
} GameVertInput;

int main() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("E: init failed -- %s", SDL_GetError());
        return 1;
    }

    SDL_GPUDevice *device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV,
        true,
        NULL);

    if (device == NULL) {
        SDL_Log("GPUCreateDevice failed");
        return -1;
    }

    SDL_Window * window = SDL_CreateWindow("clear", 800, 450, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("CreateWindow failed: %s", SDL_GetError());
        return -1;
    }

    SDL_Surface * ravioli_surface = SDL_LoadBMP("ravioli.bmp");
	if (ravioli_surface == NULL)
	{
		SDL_Log("Failed to load BMP: %s", SDL_GetError());
		return -1;
	}

	if (ravioli_surface->format != SDL_PIXELFORMAT_ABGR8888)
	{
		SDL_Surface *next = SDL_ConvertSurface(ravioli_surface, SDL_PIXELFORMAT_ABGR8888);
		SDL_DestroySurface(ravioli_surface);
		ravioli_surface = next;
	}

	if (ravioli_surface == NULL)
	{
		SDL_Log("Failed to load BMP: %s", SDL_GetError());
		return -1;
	}


    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        SDL_Log("GPUClaimWindow failed");
        return -1;
    }

    // shaders
    size_t vert_shader_bc_sz;
    void * vert_shader_bc = SDL_LoadFile("game.vert.glsl.spv", &vert_shader_bc_sz);
    if (vert_shader_bc == NULL) {
        SDL_Log("LoadFile failed: %s", SDL_GetError());
        return -1;
    }

    SDL_GPUShaderCreateInfo vert_shader_info = {
        .code = vert_shader_bc,
        .code_size = vert_shader_bc_sz,
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = SDL_GPU_SHADERSTAGE_VERTEX,
        .num_samplers = 0,
        .num_uniform_buffers = 1,
        .num_storage_buffers = 0,
        .num_storage_textures = 0,
    };

    SDL_GPUShader * vert_shader = SDL_CreateGPUShader(device, &vert_shader_info);
	if (vert_shader == NULL)
	{
		SDL_Log("Failed to create vert_shader!");
		SDL_free(vert_shader_bc);
		return 1;
	}

    size_t frag_shader_bc_sz;
    void * frag_shader_bc = SDL_LoadFile("game.frag.glsl.spv", &frag_shader_bc_sz);
    if (frag_shader_bc == NULL) {
        SDL_Log("LoadFile failed: %s", SDL_GetError());
        return -1;
    }

    SDL_GPUShaderCreateInfo frag_shader_info = {
        .code = frag_shader_bc,
        .code_size = frag_shader_bc_sz,
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
        .num_samplers = 1,
        .num_uniform_buffers = 1,
        .num_storage_buffers = 0,
        .num_storage_textures = 0,
    };

    SDL_GPUShader * frag_shader = SDL_CreateGPUShader(device, &frag_shader_info);
	if (frag_shader == NULL)
	{
		SDL_Log("Failed to create frag_shader!");
		SDL_free(frag_shader_bc);
		return 1;
	}

	// Create the pipeline
	SDL_GPUGraphicsPipelineCreateInfo pipeline_info = {
		.target_info = {
			.num_color_targets = 1,
			.color_target_descriptions = (SDL_GPUColorTargetDescription[]){{
				.format = SDL_GetGPUSwapchainTextureFormat(device, window),
			}},
		},
		// This is set up to match the vertex shader layout!
		.vertex_input_state = (SDL_GPUVertexInputState){
			.num_vertex_buffers = 1,
			.vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[]){{
				.slot = 0,
				.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
				.instance_step_rate = 0,
				.pitch = sizeof(GameVertInput)
			}},
			.num_vertex_attributes = 3,
			.vertex_attributes = (SDL_GPUVertexAttribute[]){
			// 	float p[3];
			{
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
				.location = 0,
				.offset = 0
			},
			// 	float n[3];
			{
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
				.location = 1,
				.offset = 1 * sizeof(float) * 3
			},
			// float u[2];
			{
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.location = 2,
				.offset = 2 * sizeof(float) * 3
			}}
		},
		.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
		.vertex_shader = vert_shader,
		.fragment_shader = frag_shader
	};

    SDL_GPUGraphicsPipeline * pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipeline_info);
	if (pipeline == NULL)
	{
		SDL_Log("Failed to create pipeline!");
		return -1;
	}

	SDL_ReleaseGPUShader(device, vert_shader);
	SDL_ReleaseGPUShader(device, frag_shader);

	// START TEXTURE

	SDL_GPUSampler* sampler = SDL_CreateGPUSampler(
		device,
		&(SDL_GPUSamplerCreateInfo) {
		.min_filter = SDL_GPU_FILTER_NEAREST,
		.mag_filter = SDL_GPU_FILTER_NEAREST,
		.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
		.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		}
	);

	SDL_GPUTexture* texture = SDL_CreateGPUTexture(
		device,
		&(SDL_GPUTextureCreateInfo) {
			.type = SDL_GPU_TEXTURETYPE_2D,
			.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
			.width = ravioli_surface->w,
			.height = ravioli_surface->h,
			.layer_count_or_depth = 1,
			.num_levels = 1,
			.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER
		}
	);
	SDL_SetGPUTextureName(
		device,
		texture,
		"ravioli"
	);

	// Set up texture data
	SDL_GPUTransferBuffer* textureTransferBuffer = SDL_CreateGPUTransferBuffer(
		device,
		&(SDL_GPUTransferBufferCreateInfo) {
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = ravioli_surface->w * ravioli_surface->h * 4
		}
	);

	Uint8* textureTransferPtr = SDL_MapGPUTransferBuffer(
		device,
		textureTransferBuffer,
		false
	);
	SDL_memcpy(textureTransferPtr, ravioli_surface->pixels, ravioli_surface->w * ravioli_surface->h * 4);
	SDL_UnmapGPUTransferBuffer(device, textureTransferBuffer);

	// END TEXTURE

	// START VERTEX

	// Create the vertex buffer
	SDL_GPUBuffer * vertex_buffer = SDL_CreateGPUBuffer(
		device,
		&(SDL_GPUBufferCreateInfo) {
			.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
			.size = sizeof(GameVertInput) * 4
		}
	);

	// To get data into the vertex buffer, we have to use a transfer buffer
	SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(
		device,
		&(SDL_GPUTransferBufferCreateInfo) {
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = sizeof(GameVertInput) * 4
		}
	);

	GameVertInput* transferData = SDL_MapGPUTransferBuffer(
		device,
		transferBuffer,
		false
	);

	transferData[0] = (GameVertInput) {
		.p  = { -1, -1, 0 },
		.n  = { 0, 0, 0 },
		.u  = { 0, 1 },
	};
	transferData[1] = (GameVertInput) {
		.p  = { 1, -1, 0 },
		.n  = { 0, 0, 0 },
		.u  = { 1, 0 },
	};
	transferData[2] = (GameVertInput) {
		.p  = { 0, 1, 0 },
		.n  = { 0, 0, 0 },
		.u  = { 1, 1 },
	};
	transferData[3] = (GameVertInput) {
		.p  = { -1, -1, 0 },
		.n  = { 0, 0, 0 },
		.u  = { 0, 0 },
	};

	SDL_UnmapGPUTransferBuffer(device, transferBuffer);

	// END VERTEX

	// START INDEX

	// Create the index buffer
	SDL_GPUBuffer * index_buffer = SDL_CreateGPUBuffer(
		device,
		&(SDL_GPUBufferCreateInfo) {
			.usage = SDL_GPU_BUFFERUSAGE_INDEX,
			.size = sizeof(Uint16) * 6
		}
	);

	// To get data into the index buffer, we have to use a transfer buffer
	SDL_GPUTransferBuffer* transfer_index_buffer = SDL_CreateGPUTransferBuffer(
		device,
		&(SDL_GPUTransferBufferCreateInfo) {
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = sizeof(Uint16) * 6
		}
	);

	Uint16* index_data = SDL_MapGPUTransferBuffer(
		device,
		transfer_index_buffer,
		false
	);

	index_data[0] = 0;
	index_data[1] = 1;
	index_data[2] = 2;
	index_data[3] = 3;
	index_data[4] = 1;
	index_data[5] = 2;

	SDL_UnmapGPUTransferBuffer(device, transfer_index_buffer);

	// END INDEX

	// Upload the transfer data to the vertex buffer
	SDL_GPUCommandBuffer* uploadCmdBuf = SDL_AcquireGPUCommandBuffer(device);
	SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);

	SDL_UploadToGPUTexture(
		copyPass,
		&(SDL_GPUTextureTransferInfo) {
			.transfer_buffer = textureTransferBuffer,
			.offset = 0, /* Zeros out the rest */
		},
		&(SDL_GPUTextureRegion){
			.texture = texture,
			.w = ravioli_surface->w,
			.h = ravioli_surface->h,
			.d = 1,
		},
		false
	);

	SDL_UploadToGPUBuffer(
		copyPass,
		&(SDL_GPUTransferBufferLocation) {
			.transfer_buffer = transferBuffer,
			.offset = 0
		},
		&(SDL_GPUBufferRegion) {
			.buffer = vertex_buffer,
			.offset = 0,
			.size = sizeof(GameVertInput) * 4
		},
		false
	);

	SDL_UploadToGPUBuffer(
		copyPass,
		&(SDL_GPUTransferBufferLocation) {
			.transfer_buffer = transfer_index_buffer,
			.offset = 0
		},
		&(SDL_GPUBufferRegion) {
			.buffer = index_buffer,
			.offset = 0,
			.size = sizeof(Uint16) * 6
		},
		false
	);

	SDL_DestroySurface(ravioli_surface);
	SDL_EndGPUCopyPass(copyPass);
	SDL_SubmitGPUCommandBuffer(uploadCmdBuf);
	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
	SDL_ReleaseGPUTransferBuffer(device, textureTransferBuffer);
	SDL_ReleaseGPUTransferBuffer(device, transfer_index_buffer);

    bool quit = false;

    while (!quit) {

        // check for window close
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                default:
                    break;
            }
        }

        SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(device);
        if (cmdbuf == NULL)
        {
            SDL_Log("AcquireGPUCommandBuffer failed: %s", SDL_GetError());
            return -1;
        }

        SDL_GPUTexture* swapchainTexture;
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, window, &swapchainTexture, NULL, NULL)) {
            SDL_Log("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
            return -1;
        }

        if (swapchainTexture == NULL) {
            SDL_Log("swapchainTexture == NULL: %s", SDL_GetError());
            return -1;
        }

        SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
        colorTargetInfo.texture = swapchainTexture;
        colorTargetInfo.clear_color = (SDL_FColor){ 0.3f, 0.4f, 0.5f, 1.0f };
        colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorTargetInfo, 1, NULL);

        typedef struct Load {
            float camera_pos[4];
            float model_mat[16];
            float mouse[2];
        } Load;

        // this probably needs to be packed
        // if its ever not just floats

        float c[4] = { 0, 0, -5, 16.0f/9.0f };

        static float mouse_x = 0.0f;
        mouse_x += 0.05f;

        Load loads[2] = {
            {
            .camera_pos = {c[0], c[1], c[2], c[3]},
            .model_mat = { 2.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 2.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 2.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f },
            .mouse = { mouse_x, 0 }
            },
            {
            .camera_pos = {c[0], c[1], c[2], c[3]},
            .model_mat = { 2.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 2.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 2.0f, 0.0f,
                      0.0f, 0.0f, -10.0f, 1.0f },
            .mouse = { mouse_x, 0 }
            },
        };

        SDL_BindGPUGraphicsPipeline(renderPass, pipeline);
        SDL_BindGPUVertexBuffers(renderPass, 0, &(SDL_GPUBufferBinding){ .buffer = vertex_buffer, .offset = 0 }, 1);
		SDL_BindGPUIndexBuffer(renderPass, &(SDL_GPUBufferBinding){ .buffer = index_buffer, .offset = 0 }, SDL_GPU_INDEXELEMENTSIZE_16BIT);
		
        // draw first triangle
		SDL_PushGPUVertexUniformData(cmdbuf, 0, &loads[0], sizeof(Load));
		SDL_BindGPUFragmentSamplers(renderPass, 0, &(SDL_GPUTextureSamplerBinding){ .texture = texture, .sampler = sampler }, 1);
		SDL_DrawGPUIndexedPrimitives(renderPass, 3, 1, 0, 0, 0);
		//SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

        // draw second triangle
        SDL_PushGPUVertexUniformData(cmdbuf, 0, &loads[1], sizeof(Load));
   		SDL_DrawGPUIndexedPrimitives(renderPass, 3, 1, 3, 0, 0);

		// SDL_BindGPUFragmentSamplers(renderPass, 0, &(SDL_GPUTextureSamplerBinding){ .texture = texture, .sampler = sampler }, 1);
		// SDL_DrawGPUPrimitives(renderPass, 3, 1, 3, 0);

        SDL_EndGPURenderPass(renderPass);

        SDL_SubmitGPUCommandBuffer(cmdbuf);

    }

    SDL_ReleaseWindowFromGPUDevice(device, window);
    SDL_DestroyWindow(window);
    SDL_DestroyGPUDevice(device);

    return 0;
}