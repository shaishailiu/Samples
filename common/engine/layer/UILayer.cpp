#include <algorithm>
#include "Engine.h"
#include "program/ProgramManager.h"
#include "display/Display3dUI.h"
#include "utils/BindAttrib.h"
#include "UILayer.h"

using namespace std;
UILayer::UILayer(void)
{
	regShaer();
}


UILayer::~UILayer(void)
{

}

void UILayer::update()
{
	for(unsigned int i=0;i<uilist.size();i++){
		uilist[i]->update();
	}
}

void UILayer::addChild( Display3dUI *ui )
{
	uilist.push_back(ui);
}

void UILayer::addChildAt( Display3dUI *ui,const int index )
{
	vector<Display3dUI*>::iterator it = uilist.begin();
	it += index; 
	uilist.insert(it,1,ui);
}

void UILayer::setChildIndex( Display3dUI *ui,const int index )
{
	removeChild(ui);
	addChildAt(ui,index);
}

void UILayer::removeChild( Display3dUI *ui )
{
	vector<Display3dUI*>::iterator it;
	it = find(uilist.begin(),uilist.end(),ui);

	if(it != uilist.end()){
		uilist.erase(it);
	}
}

void UILayer::removeChildAt( const int index )
{
	vector<Display3dUI*>::iterator it = uilist.begin();
	it += index; 
	if(it != uilist.end()){
		uilist.erase(it);
	}
}

Display3dUI * UILayer::getChildAt( const int index )
{
	if(index < uilist.size()){
		return uilist[index];
	}else{
		return nullptr;
	}
}

int UILayer::getChildIndex( Display3dUI *ui )
{
	for(unsigned int i =0;i<uilist.size();i++){
		if(ui == uilist[i]){
			return i;
		}
	}
	return -1;
}

void UILayer::regShaer()
{
	Engine::getProgramManager()->registShader(Display3dUI::getShaderName(),Display3dUI::getBindAtt());
}

