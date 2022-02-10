#pragma once

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <QueueFamily.h>
#include <VkValidation.h>


using namespace std;

namespace Heaven {

	class Vulkan {

	public:
		Vulkan();
		~Vulkan();

		// Vulkan setup function
		void createInstance();
		void createLogicalDevice();
		void setupDebugMessenger();
		void cleanup();

		void getPhysicalDevice();

		// support function
		bool checkInstanceExtensionSupport(vector<const char*>* checkExtensions);
		bool checkDeviceSuitable(VkPhysicalDevice device);
		bool checkValidationLayerSupport();

		QueueFamilyIndices getQueueFamily(VkPhysicalDevice device);

	private:
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkQueue graphicsQueue;
		struct {
			VkPhysicalDevice physicalDevice;
			VkDevice logicalDevice;
		} mainDevice;

	};

}