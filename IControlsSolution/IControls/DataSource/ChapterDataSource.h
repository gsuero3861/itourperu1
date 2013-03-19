#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class ChapterDataSource  sealed  :  public BindableBase
		{
		public:
			ChapterDataSource();

#pragma region Properties

		public:

			property Platform::String^ Title
			{
				void set(Platform::String^ value){ this->_title = value ; }
				Platform::String^ get(){ return this->_title ; }
			} 

			property Windows::Foundation::Collections::IVector<SectionDataSource^>^ Sections
			{
				void set(Windows::Foundation::Collections::IVector<SectionDataSource^>^ value){this->_sections = value ; }
				Windows::Foundation::Collections::IVector<SectionDataSource^>^ get(){ return _sections ; }
			}

		private:
			Platform::String^ _title ; 
			Windows::Foundation::Collections::IVector<SectionDataSource^>^ _sections ;
			 
#pragma endregion
		};
	}
}