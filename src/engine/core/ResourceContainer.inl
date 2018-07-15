namespace Engine
{
	namespace Core
	{
		template <class ResourceId, class ResourceType>
		ResourceContainer<ResourceId, ResourceType>::ResourceContainer() :
			loadCallback(nullptr),
			resources(),
			resourceFactory()
		{
		}

		template <class ResourceId, class ResourceType>
		template <class Parameter>
		void ResourceContainer<ResourceId, ResourceType>::registerResource(const ResourceId resourceId, const string& fileName, const Parameter parameter)
		{
			auto factory = resourceFactory.find(resourceId);

			// the resource shouldn't exists in the factory.
			assert(factory == resourceFactory.end());

			resourceFactory[resourceId] = [this]()
			{
				auto resource = new ResourceType();

				if (!resource->loadFromFile(fileName, parameter))
					throw std::runtime_error("Couln't open the file " + fileName);

				return ResourcePointer(resource);
			};
		}

		template <class ResourceId, class ResourceType>
		void ResourceContainer<ResourceId, ResourceType>::registerResource(const ResourceId resourceId, const string& fileName)
		{
			auto factory = resourceFactory.find(resourceId);

			// the resoruce shouldn't exists in the factory.
			assert(factory == resourceFactory.end());

			resourceFactory[resourceId] = [this, resourceId, fileName]()
			{
				auto resource = new ResourceType();

				onLoadResource(resourceId, fileName);

				if (!resource->loadFromFile(fileName))
					throw std::runtime_error("Couln't open the file " + fileName);

				return ResourcePointer(resource);
			};
		}

		template <class ResourceId, class ResourceType>
		ResourceType* ResourceContainer<ResourceId, ResourceType>::get(const ResourceId resourceId)
		{
			auto resource = resources.find(resourceId);

			// the resource should be pre-registered.
			assert(resource != resources.end());

			return &*resource->second;
		}

		template <class ResourceId, class ResourceType>
		void ResourceContainer<ResourceId, ResourceType>::loadAll()
		{
			for (auto iterator = resourceFactory.begin(); iterator != resourceFactory.end(); ++iterator)
			{
				resources[iterator->first] = (iterator->second)();
			}
		}
		
		template <class ResourceId, class ResourceType>
		void ResourceContainer<ResourceId, ResourceType>::setLoadCallback(const LoadCallback callback)
		{
			loadCallback = callback;
		}

		template <class ResourceId, class ResourceType>
		void ResourceContainer<ResourceId, ResourceType>::onLoadResource(const ResourceId resourceId, const string& fileName)
		{
			if (loadCallback == nullptr)
				return;

			loadCallback(resourceId, fileName);
		}

		template <class ResourceId, class ResourceType>
		void ResourceContainer<ResourceId, ResourceType>::clear()
		{
			resources.clear();
			resourceFactory.clear();
		}
	}
}