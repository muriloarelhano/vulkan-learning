#pragma once

#include "Vulkan.h"

namespace Heaven
{
	Vulkan::Vulkan()
	{
	}
	Vulkan::~Vulkan()
	{
	}

	void Vulkan::createInstance()
	{

		if (VkValidation.enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");

		}
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Heaven Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (VkValidation.enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(VkValidation.validationLayers.size());
			createInfo.ppEnabledLayerNames = VkValidation.validationLayers.data();

			VkValidation.populateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else {
			createInfo.enabledLayerCount = 0;

			createInfo.pNext = nullptr;
		}

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void Vulkan::createLogicalDevice()
	{

		// Get the queue family indices for the chosen physical device
		QueueFamilyIndices indices = getQueueFamily(mainDevice.physicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo = { };
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.queueFamililyIndice; // index of teh family to create queue
		queueCreateInfo.queueCount = 1;

		float priority = 1.0f; // Most important
		queueCreateInfo.pQueuePriorities = &priority;
		VkDeviceCreateInfo deviceCreateInfo = {}; // Priotity to vulkan knows how handle multiple queues

		// Information to create logical device
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = 1;
		deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
		deviceCreateInfo.enabledExtensionCount = 0;
		deviceCreateInfo.ppEnabledExtensionNames = nullptr;
		deviceCreateInfo.enabledLayerCount = 0;

		VkPhysicalDeviceFeatures deviceFeatures = {};
		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;	// Physical device features logical device will use
		VkResult result = vkCreateDevice(mainDevice.physicalDevice, &deviceCreateInfo, nullptr, &mainDevice.logicalDevice);
		if (result != VK_SUCCESS) throw runtime_error("Failed to create a logical device");

		//Queues are create at same time as the device...
		// So we quant handle de queues
		vkGetDeviceQueue(mainDevice.logicalDevice, indices.queueFamililyIndice, 0, &graphicsQueue);
	}

	void Vulkan::setupDebugMessenger() {
		if (!VkValidation.enableValidationLayers) return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		VkValidation.populateDebugMessengerCreateInfo(createInfo);

		if (VkValidation::CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
			throw std::runtime_error("failed to set up debug messenger!");
		}
	}


	void Vulkan::cleanup()
	{
		if (VkValidation.enableValidationLayers) {
			VkValidation::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
		}
		vkDestroyDevice(mainDevice.logicalDevice, nullptr);
		vkDestroyInstance(instance, nullptr);
	}

	void Vulkan::getPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0) {
			throw runtime_error("Can't find GPUs with support vulkan");
		}

		vector<VkPhysicalDevice> deviceList(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.data());

		mainDevice.physicalDevice = deviceList[0];

		for (const auto& device : deviceList) {
			if (checkDeviceSuitable(device)) {
				mainDevice.physicalDevice = device;
				break;
			}
		}
	}

	bool Vulkan::checkInstanceExtensionSupport(vector<const char*>* checkExtensions)
	{
		// Need to get number of extensions to create array of correct size to hold extension
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);


		vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		for (const auto& checkExtension : *checkExtensions)
		{
			bool hasExtension = false;
			for (const auto& extension : extensions)
			{
				if (strcmp(checkExtension, extension.extensionName))
				{
					hasExtension = true;
					break;
				}
			}

			if (!hasExtension)
			{
				return false;
			}


		}
		return true;
	}

	bool Vulkan::checkDeviceSuitable(VkPhysicalDevice device)
	{
		// Information about the device itself
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		// Information about whats the device can do (features)
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		QueueFamilyIndices indices = getQueueFamily(device);

		return indices.isValid();
	}

	bool Vulkan::checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : VkValidation.validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	std::vector<const char*> Vulkan::getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (VkValidation.enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	QueueFamilyIndices Vulkan::getQueueFamily(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilyList) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.queueFamililyIndice = i;
			}

			if (indices.isValid()) {
				break;
			}

			i++;
		}

		return indices;
	}

}