#pragma once

#include "externals/il2cpp-api.h"
#include "externals/System/Primitives.h"
#include "externals/System/String.h"
#include "externals/UnityEngine/Coroutine.h"

namespace System::Collections::Generic {
    template <typename T, typename K, typename V>
    struct Dictionary : ILClass<T> {
        struct Entry : ILStruct<Entry> {
            struct Fields {
                int32_t hashCode;
                int32_t next;
                K::Object* key;
                V::Object* value;
            };
        };

        struct Fields {
            System::Int32_array* buckets;
            Entry::Array* entries;
            int32_t count;
            int32_t version;
            int32_t freeList;
            int32_t freeCount;
            void* comparer;
            void* keys;
            void* values;
            Il2CppObject* _syncRoot;
        };

        inline void Add(typename K::Object* key, typename V::Object* value, MethodInfo* mi) {
            this->template external<void>(0x02881030, this, key, value, mi);
        }
    };

    struct Dictionary$$Coroutine : ILClass<Dictionary<Dictionary$$Coroutine, UnityEngine::Coroutine, UnityEngine::Coroutine>> {
        static inline StaticILMethod<0x04c884a8> Method$System_Collections_Generic_Dictionary__Coroutine_Coroutine__$$Add_ {};
    };


}
