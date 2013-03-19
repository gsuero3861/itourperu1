#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class SectionDataSource sealed  :  public BindableBase
		{
		public:
			SectionDataSource();

#pragma region Properties

		public:

			property Platform::String^ Title
			{
				void set(Platform::String^ value){ this->_title = value ; }
				Platform::String^ get(){ return this->_title ; }
			}

			property Platform::String^ FrameSource
			{
				void set(Platform::String^ value){ this->_framesource = value ; }
				Platform::String^ get(){ return this->_framesource ; }
			}

			property Windows::Foundation::Collections::IVector<PageDataSource^>^ Pages
			{
				void set(Windows::Foundation::Collections::IVector<PageDataSource^>^ value){this->_pages = value ; }
				Windows::Foundation::Collections::IVector<PageDataSource^>^ get(){ return _pages ; }
			}

		private:
			Platform::String^ _title ;
			Platform::String^ _framesource ;
			Windows::Foundation::Collections::IVector<PageDataSource^>^ _pages ;
			 
#pragma endregion

		};
	}
}