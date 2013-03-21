#include "pch.h"

namespace IControls
{
	public delegate void AnimationViewCompletedEventHandler(Platform::Object ^ sender  );

	public ref class AnimationView sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		AnimationView();
		event AnimationViewCompletedEventHandler ^ AnimationViewCompleted ;

#pragma region Properties
	public:

		property float64 ItemWidth
		{
			void set(float64 value){ 
				this->_itemwidth =  value ; 
				this->Width =  value ;
			}
			float64 get(){ return this->_itemwidth  ;}
		}

		property float64 ItemHeight
		{
			void set(float64 value){  
				this->Height =  value ;
				this->_itemheight =  value ; }
			float64 get(){ return  this->ItemHeight ;}
		} 

		property int32 InitialItem
		{
			void set(int32 value){ this->_initialitem =  value ; }
			int32 get(){ return this->_initialitem ;}
		} 

		property DataSource::SectionDataSource ^ AnimationSource
		{
			void set(DataSource::SectionDataSource ^ value)
			{
				this->_datasource =  value ; 
				inititemsgrid();
			}
			DataSource::SectionDataSource ^ get(){ return this->_datasource ;}
		}

	private:
		int32 _initialitem ;
		float64 _itemwidth, _itemheight ;
		DataSource::SectionDataSource ^ _datasource ;
		

#pragma endregion

#pragma region Controls

	private :
		Windows::UI::Xaml::Controls::Grid^ _itemspanel ;
		Windows::UI::Xaml::Media::CompositeTransform ^ _paneltransform ;
		void inititemsgrid();

#pragma endregion

#pragma region Methods

	public :
		void SetOutAnimation(int32 _item);
		void AnimateOut();

	private:
		void AnimationViewItem_Completed(Platform::Object ^ sender  );

#pragma endregion

	}; 
}