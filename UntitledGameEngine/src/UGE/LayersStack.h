#pragma once
#include "ugepch.h"
#include "Layer.h"

namespace UGE {
	class UGE_API LayersStack
	{
	public:
		LayersStack() = default;
		~LayersStack();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); };
		std::vector<Layer*>::iterator end() { return m_layers.end(); };
		std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); };
		std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); };

	private:
		std::vector<Layer*> m_layers;
		int m_layer_insert_index = 0;
	};
}
