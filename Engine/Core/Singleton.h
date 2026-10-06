#pragma once

namespace ChiefEngine {
    template <typename T>
    class Singleton {
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        static T& Instance() {
            static T instance;
            return instance;
        }

    protected:
        Singleton() = default;
    };
}