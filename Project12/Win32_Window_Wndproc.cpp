#include "hander.h"
#include <iostream>

namespace FCT {

	LRESULT Win32_D3D11_Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Win32_D3D11_Window* pWnd = (Win32_D3D11_Window*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
		switch (message)
		{
		case WM_NCCREATE:
		{
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			pWnd = (Win32_D3D11_Window*)cs->lpCreateParams;
			RECT rc;
			pWnd->m_x = cs->x;
			pWnd->m_y = cs->y;
			pWnd->m_width = cs->cx;
			pWnd->m_height = cs->cy;
			//注意此时还在执行CreateWindow，m_hWnd还未赋值
			pWnd->m_wnd = hWnd;
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
			break;
		}
		case WM_CREATE:
		{
			{
				pWnd->m_buffer = new Color[pWnd->m_width * pWnd->m_height];
				for (int i = 0; i < pWnd->m_width * pWnd->m_height; i++) {
					pWnd->m_buffer[i] = { 1,1,0,1 };
				}
			}
			//d3d11
			{
				//创建device
				{
					D3D_FEATURE_LEVEL featureLevels[] = {
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0, };
					D3D11CreateDevice(NULL,
						D3D_DRIVER_TYPE_HARDWARE,
						0,
						D3D11_CREATE_DEVICE_DEBUG,
						featureLevels
						, 2,
						D3D11_SDK_VERSION,
						&pWnd->m_device,
						NULL,
						&pWnd->m_context);
				}
				//创建交换链
				{
					IDXGIFactory* pDXGIFactory = NULL;
					CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);

					DXGI_SWAP_CHAIN_DESC SwapChainParam;

					DXGI_MODE_DESC BufferParam;
					BufferParam.Width = 800;
					BufferParam.Height = 600;
					BufferParam.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					BufferParam.RefreshRate.Numerator = 60;
					BufferParam.RefreshRate.Denominator = 1;
					BufferParam.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
					BufferParam.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

					DXGI_SAMPLE_DESC SampleParam;
					SampleParam.Count = 1;
					SampleParam.Quality = 0;

					SwapChainParam.Flags = 0;
					SwapChainParam.BufferCount = 1;
					SwapChainParam.BufferDesc = BufferParam;
					SwapChainParam.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					SwapChainParam.OutputWindow = pWnd->m_wnd;
					SwapChainParam.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
					SwapChainParam.SampleDesc = SampleParam;
					SwapChainParam.Windowed = true;

					pDXGIFactory->CreateSwapChain(pWnd->m_device,
						&SwapChainParam, &pWnd->m_swapChain);
					pDXGIFactory->Release();
				}
				//创建d3d11 buffer and view并绑定
				{
					ID3D11Texture2D* pBackBuffer = NULL;
					pWnd->m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
					pWnd->m_device->CreateRenderTargetView(pBackBuffer, NULL, &pWnd->m_renderTargetView);

					ID3D11Texture2D* pDepthBuffer = NULL;
					D3D11_TEXTURE2D_DESC depthStencilData;
					depthStencilData.Width = 800;
					depthStencilData.Height = 600;
					depthStencilData.MipLevels = 1;
					depthStencilData.ArraySize = 1;
					depthStencilData.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
					depthStencilData.SampleDesc.Count = 1;
					depthStencilData.SampleDesc.Quality = 0;
					depthStencilData.Usage = D3D11_USAGE_DEFAULT;
					depthStencilData.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					depthStencilData.CPUAccessFlags = 0;
					depthStencilData.MiscFlags = 0;

					pWnd->m_device->CreateTexture2D(&depthStencilData, NULL, &pDepthBuffer);
					pWnd->m_device->CreateDepthStencilView(pDepthBuffer, NULL, &pWnd->m_depthStencilView);
					pWnd->m_context->OMSetRenderTargets(1, &pWnd->m_renderTargetView, pWnd->m_depthStencilView);
				}
				//编译并创建并绑定顶点着色器与input layout
				{
					const char* VertexShaderCode =
						"Texture2D texcoord : register(t0);"
						"struct VSOut"
						"{"
						"float4 pos : SV_Position;"
						"float4 color : Color;"
						"float2 tex : Texcoord;"
						"};"
						"VSOut main(float4 color : Color,float3 pos : Position,float2 tex : Texcoord)"
						"{"
						"	VSOut ret;"
						"	ret.pos = float4(pos.x,pos.y,pos.z,1.0f);"
						"	ret.color = color;"
						"	ret.tex = tex;"
						"	return ret;"
						"}"
						;
					ID3DBlob* ErrorMessage = NULL;
					ID3DBlob* VertexShaderCompiled = NULL;
					D3DCompile(VertexShaderCode, strlen(VertexShaderCode)
						, NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
						"main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &VertexShaderCompiled, &ErrorMessage);
					if (ErrorMessage) {
						//Todo error
						ErrorMessage->Release();
					}
					pWnd->m_device->CreateVertexShader(VertexShaderCompiled->GetBufferPointer(), VertexShaderCompiled->GetBufferSize(),
						NULL, &pWnd->m_vertexShader);
					pWnd->m_context->VSSetShader(pWnd->m_vertexShader, NULL, 0);
					D3D11_INPUT_ELEMENT_DESC layout[] =
					{
						{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
						{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
						{ "Texcoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					};
					UINT numElements = ARRAYSIZE(layout);
					pWnd->m_device->CreateInputLayout(layout, numElements,
						VertexShaderCompiled->GetBufferPointer(), VertexShaderCompiled->GetBufferSize(), &pWnd->m_inputLayout);
					pWnd->m_context->IASetInputLayout(pWnd->m_inputLayout);
					VertexShaderCompiled->Release();
				}
				//编译并创建并绑定像素着色器
				{
					const char* PixelShaderCode =
						"Texture2D texcoord : register(t0);"
						"SamplerState g_sampler : register(s0);"
						"float4 main(float4 pos : SV_Position,float4 color : Color,float2 tex : Texcoord ) : SV_Target"
						"{"
						"    return texcoord.Sample(g_sampler, tex); "
						"}"
						;
					//"	return color;"
					ID3DBlob* PixelShaderCompiled = NULL;
					ID3DBlob* ErrorMessage = NULL;
					D3DCompile(PixelShaderCode, strlen(PixelShaderCode),
						NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
						"main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &PixelShaderCompiled, &ErrorMessage);
					if (ErrorMessage) {
						std::cout << (char*)ErrorMessage->GetBufferPointer();
						//Todo error
						ErrorMessage->Release();
					}
					pWnd->m_device->CreatePixelShader(PixelShaderCompiled->GetBufferPointer(), PixelShaderCompiled->GetBufferSize(),
						NULL, &pWnd->m_pixelShader);
					pWnd->m_context->PSSetShader(pWnd->m_pixelShader, NULL, 0);
					PixelShaderCompiled->Release();
				}
				//viewport
				{
					D3D11_VIEWPORT vp;
					vp.Width = pWnd->m_width;
					vp.Height = pWnd->m_height;
					vp.MinDepth = 0.0f;
					vp.MaxDepth = 1.0f;
					vp.TopLeftX = 0;
					vp.TopLeftY = 0;
					pWnd->m_context->RSSetViewports(1, &vp);
				}
				//纹理采样
				{
					D3D11_SAMPLER_DESC sampDesc;
					ZeroMemory(&sampDesc, sizeof(sampDesc));
					sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
					sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
					sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
					sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
					sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
					sampDesc.MinLOD = 0;
					sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
					pWnd->m_device->CreateSamplerState(&sampDesc, &pWnd->m_samplerState);
					pWnd->m_context->PSSetSamplers(0, 1, &pWnd->m_samplerState);

				}
				//创建纹理(buffer)
				{
					D3D11_TEXTURE2D_DESC desc;
					desc.SampleDesc.Count = 1;
					desc.SampleDesc.Quality = 0;
					desc.Width = pWnd->m_width;
					desc.Height = pWnd->m_height;
					desc.MipLevels = 1;
					desc.ArraySize = 1;
					desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					desc.SampleDesc.Count = 1;
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					desc.MiscFlags = 0;

					D3D11_SUBRESOURCE_DATA resource_data;
					resource_data.pSysMem = pWnd->m_buffer;
					resource_data.SysMemPitch = pWnd->m_width * sizeof(Color);
					resource_data.SysMemSlicePitch = 0;
					pWnd->m_device->CreateTexture2D(&desc, &resource_data, &pWnd->m_bufferTexture);
					D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
					srvDesc.Format = desc.Format;
					srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					srvDesc.Texture2D.MostDetailedMip = 0;
					srvDesc.Texture2D.MipLevels = desc.MipLevels;

					pWnd->m_device->CreateShaderResourceView(pWnd->m_bufferTexture, &srvDesc, &pWnd->m_bufferTextureView);
					pWnd->m_context->PSSetShaderResources(0, 1, &pWnd->m_bufferTextureView);
				}

				//创建长方形buffer
				{

					static Vertex pVertexBuffer[4] = {
						{{-1.0,-1.0,0},{1,0,0,1},{0,1} },
						{{-1.0, 1.0,0},{0,0,1,1},{0,0} },
						{{ 1.0,-1.0,0},{0,0,1,1},{1,1} },
						{{ 1.0, 1.0,0},{0,1,0,1},{1,0} }
					};
					UINT stride = 0;
					UINT offset = 0;

					D3D11_SUBRESOURCE_DATA resource_data;
					resource_data.pSysMem = pVertexBuffer;
					resource_data.SysMemPitch = 0;
					resource_data.SysMemSlicePitch = 0;


					D3D11_BUFFER_DESC buffer_data;
					buffer_data.ByteWidth = sizeof(Vertex) * 4;
					buffer_data.Usage = D3D11_USAGE_DYNAMIC;
					buffer_data.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					buffer_data.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					buffer_data.MiscFlags = 0;
					buffer_data.StructureByteStride = 0;
					pWnd->m_device->CreateBuffer(&buffer_data, &resource_data, &pWnd->m_vertexBuffer);


				}
			}
			pWnd->flush();
			//
			break;
		}
		case WM_PAINT:
		{
			pWnd->m_swapChain->Present(1, 0);
			break;
		}
		case WM_LBUTTONDOWN:
			int x;
			int y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			pWnd->m_buffer[(y)*pWnd->m_width + x] = { 0,0,1,1 };
			break;
			//return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_KEYDOWN:
			if (wParam == 'F') {
				pWnd->flush();
			}
			break;
			//return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_MOVE:
			pWnd->m_x = GET_X_LPARAM(lParam);
			pWnd->m_y = GET_Y_LPARAM(lParam);
			break;
			//return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_SIZE:
			if (pWnd->m_width == LOWORD(lParam) && pWnd->m_height == HIWORD(lParam)) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			if (pWnd->m_width * pWnd->m_height != LOWORD(lParam) * HIWORD(lParam)) {
				delete[] pWnd->m_buffer;
				pWnd->m_buffer = new Color[LOWORD(lParam) * HIWORD(lParam)];
			}
			//directx resize
			{

			}
			pWnd->m_width = LOWORD(lParam);
			pWnd->m_height = HIWORD(lParam);
			break;
			//return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
			//return DefWindowProc(hWnd, message, wParam, lParam);
		}
		//return DefWindowProc(hWnd, message, wParam, lParam);;
		return pWnd->m_input->WndProc(hWnd, message, wParam, lParam);
	}
	//Todo:重构,把绘图和Win api部分分开
}