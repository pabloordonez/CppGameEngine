#ifndef __ENGINE_CORE_RESOURCE_CONTAINER_H__
#define __ENGINE_CORE_RESOURCE_CONTAINER_H__

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <assert.h>

namespace Engine
{
	namespace Core
	{
		using std::string;
		using std::unique_ptr;
		using std::function;
		using std::map;

		template <class ResourceId, class ResourceType>
		class ResourceContainer
		{
		public:
			typedef function<void(const ResourceId resourceId, const string& fileName)> LoadCallback;
			typedef unique_ptr<ResourceType> ResourcePointer;

		public:
			ResourceContainer();

			template <class Parameter>
			void registerResource(const ResourceId resourceId, const string& fileName, const Parameter parameter);
			void registerResource(const ResourceId resourceId, const string& fileName);
			ResourceType* get(const ResourceId resourceId);
			void loadAll();
			void setLoadCallback(const LoadCallback callback);
			void clear();

		private:
			void onLoadResource(const ResourceId resourceId, const string& fileName);

		private:
			LoadCallback loadCallback;
			map<ResourceId, ResourcePointer> resources;
			map<ResourceId, function<ResourcePointer()>> resourceFactory;
		};
	}
}

#include "ResourceContainer.inl"

#endif