#pragma once

class FuncHook {
public:
	virtual bool InitializeHook() = 0;
};

// Hooks Include
#pragma region Hooks Include

// Actor

//Game

//Input

//Render

#pragma endregion


// This function initializes all registered function hooks
void InitializeHooks() {
	// This is an array of pointers to function hook objects
	static FuncHook* Hooks[] = { // This is to store out hooks.
		// Now in the FuncHook class here register the hooks.
			nullptr
	};

	for (std::size_t i = 0; i < std::size(Hooks); ++i) {
		if (!Hooks[i]->InitializeHook()) {
			//hooks failure code here
		}
	}
}