
# RenderGraph的编译流程

RenderGraph的编译流程主要分为三个阶段：Pass添加阶段、尺寸统一阶段和编译阶段。

## 流程概述

```mermaid
graph LR
    subgraph addPass["Pass添加阶段"]
        getImageNode[获取图片节点]
        mergeInfo[合并信息]
        fillInfo[填充信息并创建]
        createEdge[添加边]
        uniteAllOutput[将所有用于pass输出的节点unite]
        
        getImageNode --> |存在| mergeInfo
        getImageNode --> |不存在| fillInfo
        mergeInfo --> createEdge
        fillInfo --> createEdge
        createEdge --> uniteAllOutput
    end
    
    subgraph compile["编译阶段"]
        subgraph resolveTextureSizes["解析纹理尺寸"]
            A1[遍历所有Pass]
            A2[遍历所有texture边]
            A3[如果该texture所连的image的大小还不能确定<br/>且texture没有指定相对或绝对大小<br/>为其填充相对target大小1:1]
            A4[unite相对target大小的texture大小]
            
            A1 --> A2 --> A3 --> A4
        end
        
        subgraph groupPasses["分组Pass"]
            B1[遍历pass]
            B2[如果texture连接的image和pass输出大小相同<br/>将该texture作为target的pass全部Unite起来]
            B3[遍历image]
            B4[将输出到这个image的pass全部unite起来]
            
            B1 --> B2 --> B3 --> B4
        end
        
        subgraph allocateImage["分配图像资源"]
            C1[将所有image如果还有undefined的参数<br/>填为默认参数]
            C2[用resourceManager分配资源]
            
            C1 --> C2
        end
        
        subgraph createRHIPass["创建RHI Pass"]
            D1[创建rhi pass]
        end
        
        subgraph createPassGroup["创建Pass组"]
            E1[创建pass group]
        end
        
        subgraph computePassGroupExecutionOrder["计算执行顺序"]
            F1[根据依赖对passgroup实现拓扑排序]
            F2[用模拟法，模拟执行一遍来判断需要什么屏障存起来]
            
            F1 --> F2
        end
        
        resolveTextureSizes --> groupPasses
        groupPasses --> allocateImage
        allocateImage --> createRHIPass
        createRHIPass --> createPassGroup
        createPassGroup --> computePassGroupExecutionOrder
    end
    
    addPass --> compile