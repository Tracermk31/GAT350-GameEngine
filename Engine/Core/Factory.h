#pragma once

#include "Framework/Object.h"
#include "Singleton.h"
#include "EngineStrings.h"

#include <map>
#include <memory>

#define FACTORY_REGISTER(className)                                             \
    class Register##className {                                                 \
    public:                                                                     \
        Register##className() {                                                 \
            ChiefEngine::Factory::Instance().Register<##className>(#className); \
        }                                                                       \
    };                                                                          \
    static Register##className registerInstance;

namespace ChiefEngine {
    class ICreator {
    public:
        virtual ~ICreator() = default;
        virtual std::unique_ptr<Object> Create() = 0;
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class Creator : public ICreator {
    public:
        ~Creator() = default;
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        std::unique_ptr<Object> Create() override { return std::make_unique<T>(); }
    };

    template <typename T>
        requires std::derived_from<T, Object>
    class PrototypeCreator : public ICreator {
    public:
        ~PrototypeCreator() = default;
        PrototypeCreator(std::unique_ptr<Object> prototype) : 
            m_prototype{ std::move(prototype) }
        {}

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        std::unique_ptr<Object> Create() override { 
            return m_prototype->Clone();
        }
    private:
        std::unique_ptr<Object> m_prototype;
    };

    class Factory : public Singleton<Factory> {
    public:
        template <typename T>
            requires std::derived_from<T, Object>
        inline void Register(const std::string& name);

        template <typename T>
            requires std::derived_from<T, Object>
        inline void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

        template <typename T = class Object>
            requires std::derived_from<T, Object>
        inline std::unique_ptr<T> Create(const std::string& name);
    private:
        std::map<std::string, std::unique_ptr<ICreator>> m_registry;
    };

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="name"></param>
    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::Register(const std::string& name) {
        std::string id = ToLower(name);
        if (m_registry.contains(id)) {
            std::cerr << name << " already registered in Object Registry\n";
            return;
        }
        std::cout << "Object registered: " << name << std::endl;

        m_registry[id] = std::make_unique<Creator<T>>();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="name"></param>
    /// <param name="prototype"></param>
    template <typename T>
        requires std::derived_from<T, Object>
    inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype) {
        std::string id = ToLower(name);
        if (m_registry.contains(id)) {
            std::cerr << name << " already registered in Object Registry\n";
            return;
        }
        m_registry[id] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="name"></param>
    /// <returns></returns>
    template <typename T>
        requires std::derived_from<T, Object>
    inline std::unique_ptr<T> Factory::Create(const std::string& name) {
        std::string id = ToLower(name);

        if (!m_registry.contains(id)) {
            std::cerr << name << " not registered in Object Registry\n";
            return std::unique_ptr<T>();
        }

        auto object = m_registry[id]->Create();

        T* derived = dynamic_cast<T*>(object.get());
        
        if (derived) {
            object.release();
            return std::unique_ptr<T>(derived);
        } else {
            std::cerr << name << " and Object type mismatch\n";
            return std::unique_ptr<T>();
        }
    }
}