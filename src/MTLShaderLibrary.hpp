#pragma once
#include "ShaderLibrary.hpp"
#include <Metal/Metal.h>
#include <string_view>
#include <memory>

namespace RGL{
    struct DeviceMTL;

    struct ShaderLibraryMTL : public IShaderLibrary{
        id<MTLFunction> function = nullptr;
        const std::shared_ptr<DeviceMTL> owningDevice;
        
        ShaderLibraryMTL(decltype(owningDevice), const std::string_view);
        
        virtual ~ShaderLibraryMTL(){}
    };
}