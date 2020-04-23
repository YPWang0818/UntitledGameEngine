#include "ugepch.h"
#include "LayersStack.h"

namespace UGE {

	LayersStack::~LayersStack() {
		for (Layer* layer : m_layers) {

			layer->onDetach();
			delete layer;
		};
	};

	void LayersStack::PushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
		m_layer_insert_index++;
	};

	void LayersStack::PushOverLay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	};

	void LayersStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_insert_index, layer);
		if (it != m_layers.begin() + m_layer_insert_index) {
			layer->onDetach();
			m_layers.erase(it);
			m_layer_insert_index--;
		};
	}

	void LayersStack::PopOverLay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end() , overlay);
		if (it != m_layers.end()) {
			overlay->onDetach();
			m_layers.erase(it);
		};
	}

}
