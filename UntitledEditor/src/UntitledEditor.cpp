#include "UGE/core/EntryPoint.h"
#include "EditorLayer.h"

namespace UE {

	class UntitledEditor : public UGE::Application
	{
	public:

		UntitledEditor() {

			PushLayer(new EditorLayer());

		}
		~UntitledEditor() {

		}


	};


}
	UGE::Application* UGE::createApp()
	{

		return new UE::UntitledEditor();
	}











