#pragma once

#include "externals/il2cpp-api.h"

namespace System {
    struct Delegate : ILClass<Delegate> {
        struct Fields {
            intptr_t method_ptr;
            intptr_t invoke_impl;
            Il2CppObject* m_target;
            MethodInfo* method;
            intptr_t delegate_trampoline;
            intptr_t extra_arg;
            intptr_t method_code;
            void* method_info;
            void* original_method_info;
            void* data;
            bool method_is_virtual;
        };

        static inline Delegate::Object* Combine(Delegate::Object* a, Delegate::Object* b) {
            return external<Delegate::Object*>(0x024897f0, a, b);
        }
    };
}
