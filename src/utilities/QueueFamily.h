#pragma once

struct QueueFamilyIndices {
	int queueFamililyIndice = -1;

	bool isValid()
	{
		return queueFamililyIndice >= 0;
	}
};