#include "pch.h"

#include "ModelComponent.h"

#include "Core/Factory.h"

namespace ChiefEngine {
	FACTORY_REGISTER(ModelComponent)

	void ModelComponent::Draw(const Renderer& renderer) const {

	}

	void ModelComponent::Read(const JSON::value_t& value) {

	}
}