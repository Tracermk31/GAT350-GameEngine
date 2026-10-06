#pragma once

#include <memory>

namespace ChiefEngine {
	class Resource {
	public:
		Resource() = default;
		virtual ~Resource() = default;
	};

	template <typename T = Resource>
	using resource_t = std::shared_ptr<T>;
}