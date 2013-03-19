#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class BookDataSource  sealed :  public BindableBase	
		{
		public:
			BookDataSource();

			#pragma region Properties

		public:

			property Platform::String^ Title
			{
				void set(Platform::String^ value){ this->_title = value ; }
				Platform::String^ get(){ return this->_title ; }
			} 

			property Windows::Foundation::Collections::IVector<ChapterDataSource^>^ Chapters
			{
				void set(Windows::Foundation::Collections::IVector<ChapterDataSource^>^ value){this->_chapters = value ; }
				Windows::Foundation::Collections::IVector<ChapterDataSource^>^ get(){ return _chapters ; }
			}

		private:
			Platform::String^ _title ; 
			Windows::Foundation::Collections::IVector<ChapterDataSource^>^ _chapters ;
			 
#pragma endregion
		};
	}
}