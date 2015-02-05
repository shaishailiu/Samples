#include "Engine.h"
#include "display/gemo/Display3dGrid.h"
#include "display/gemo/Display3dCube.h"
#include "display/gemo/Display3dAxis.h"
#include "program/ProgramManager.h"
#include "utils/BindAttrib.h"
#include "GeomLayer.h"


GeomLayer::GeomLayer(void)
{
	Engine::getProgramManager()->registShader(Display3dGrid::getShaderName(),Display3dGrid::getBindAtt());
	Engine::getProgramManager()->registShader(Display3dCube::getShaderName(),Display3dCube::getBindAtt());
	Engine::getProgramManager()->registShader(Display3dAxis::getShaderName(),Display3dAxis::getBindAtt());

	grid = new Display3dGrid();
	grid->program = Engine::getProgramManager()->getShader(Display3dGrid::getShaderName());
	grid->initGridNum();


	cube = new Display3dCube();
	cube->program = Engine::getProgramManager()->getShader(Display3dCube::getShaderName());

	axis = new Display3dAxis();
	axis->program = Engine::getProgramManager()->getShader(Display3dAxis::getShaderName());

}


GeomLayer::~GeomLayer(void)
{
}

void GeomLayer::update()
{
	//grid->update();
	//cube->update();
	axis->update();
}
