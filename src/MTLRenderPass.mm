#if RGL_MTL_AVAILABLE
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#include "MTLRenderPass.hpp"
#include "RGLCommon.hpp"
#include "MTLTexture.hpp"

namespace RGL{


MTLLoadAction rgl2mtlload(LoadAccessOperation op){
    switch(op){
        case LoadAccessOperation::Load:
            return MTLLoadActionLoad;
        case LoadAccessOperation::Clear:
            return MTLLoadActionClear;
        case LoadAccessOperation::DontCare:
        case LoadAccessOperation::NotAccessed:
            return MTLLoadActionDontCare;
    }
}

MTLStoreAction rgl2mtlstore(StoreAccessOperation op){
    switch(op){
        case decltype(op)::Store:
            return MTLStoreActionStore;
        case StoreAccessOperation::None:
        case decltype(op)::DontCare:
            return MTLStoreActionDontCare;
        default:
            FatalError("selected StoreOp is not implemented");
    }
}


RenderPassMTL::RenderPassMTL(const RenderPassConfig& config){
    renderPassDescriptor = [MTLRenderPassDescriptor new];
    
    uint32_t idx = 0;
    for(const auto& attachmentdesc : config.attachments){
        auto attachment = renderPassDescriptor.colorAttachments[idx];
        [attachment setLoadAction:rgl2mtlload(attachmentdesc.loadOp)];
        [attachment setStoreAction:rgl2mtlstore(attachmentdesc.storeOp)];
        [attachment setClearColor:MTLClearColorMake(attachmentdesc.clearColor[0], attachmentdesc.clearColor[1], attachmentdesc.clearColor[2], attachmentdesc.clearColor[3])];
        idx++;
    }
  
    
#if TARGET_OS_IPHONE
    [renderPassDescriptor setDefaultRasterSampleCount:0];
#else
    [renderPassDescriptor setDefaultRasterSampleCount:static_cast<int>(0)]; //TODO: multisample config
#endif
}

void RenderPassMTL::SetAttachmentTexture(uint32_t index, ITexture* texture){
    [renderPassDescriptor.colorAttachments[index] setTexture:static_cast<TextureMTL*>(texture)->texture];
}

}

#endif