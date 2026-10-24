#include "cRadar.h"
#include "SDK.h"

bool bSave_Radar_Pos = true;
int radarSize = 110; // <--- Изменили имя переменной

void cRadar::DrawRadar()
{
	if (!Ikaros.m_pCvars->bRadar2D)
		return;

	// Везде ниже заменили size на radarSize
	if (Ikaros.m_pMouse->IsInBox(Ikaros.m_pCvars->flRadarPos_x - (radarSize / 2) - 6, Ikaros.m_pCvars->flRadarPos_y - (radarSize / 2) - 6, radarSize * 2 + 12, radarSize * 2 + 12) && Ikaros.m_pMouse->bMouse1pressed)
	{
		if (!bSave_Radar_Pos)
		{
			Ikaros.m_pCvars->iSavedRadarX = Ikaros.m_pCvars->iMouseX - Ikaros.m_pCvars->flRadarPos_x;
			Ikaros.m_pCvars->iSavedRadarY = Ikaros.m_pCvars->iMouseY - Ikaros.m_pCvars->flRadarPos_y;
			bSave_Radar_Pos = true;
		}
		Ikaros.m_pCvars->flRadarPos_x = Ikaros.m_pCvars->iMouseX;
		Ikaros.m_pCvars->flRadarPos_y = Ikaros.m_pCvars->iMouseY;
		Ikaros.m_pCvars->flRadarPos_x = Ikaros.m_pCvars->flRadarPos_x - Ikaros.m_pCvars->iSavedRadarX;
		Ikaros.m_pCvars->flRadarPos_y = Ikaros.m_pCvars->flRadarPos_y - Ikaros.m_pCvars->iSavedRadarY;
	}
	else
	{
		bSave_Radar_Pos = false;
	}

	int centerx = Ikaros.m_pCvars->flRadarPos_x + (radarSize / 2); // <--- radarSize
	int centery = Ikaros.m_pCvars->flRadarPos_y + (radarSize / 2); // <--- radarSize
	if (Ikaros.m_pCvars->bRadarBG)
	{
		Ikaros.m_pDraw->FillRGBA(centerx, centery - radarSize, 1, 2 * radarSize, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK)); // <--- radarSize
		Ikaros.m_pDraw->FillRGBA(centerx - radarSize, centery, 2 * radarSize, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK)); // <--- radarSize
	}
	else
	{
		Ikaros.m_pDraw->Border(centerx - radarSize - 6, centery - radarSize - 6, 2 * radarSize + 6, 2 * radarSize + 6, 6, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor)); // <--- radarSize
		Ikaros.m_pDraw->FillRGBA(centerx - radarSize, centery - radarSize, 2 * radarSize, 2 * radarSize, RED(BackgroundColor), GREEN(BackgroundColor), BLUE(BackgroundColor), ALPHA(BackgroundColor)); // <--- radarSize
		Ikaros.m_pDraw->FillRGBA(centerx, centery - radarSize, 1, 2 * radarSize, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor)); // <--- radarSize
		Ikaros.m_pDraw->FillRGBA(centerx - radarSize, centery, 2 * radarSize, 1, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor)); // <--- radarSize
		Ikaros.m_pDraw->FillRGBA(centerx - radarSize - 6, centery - radarSize - 22, 232, 25, RED(MenuColor), GREEN(MenuColor), BLUE(MenuColor), ALPHA(MenuColor)); // <--- radarSize
		Ikaros.m_pDraw->Text(centerx - radarSize, centery - radarSize - 15, RED(FontColor), GREEN(FontColor), BLUE(FontColor), ALPHA(FontColor), "Radar"); // <--- radarSize
		Ikaros.m_pDraw->Border(centerx - radarSize - 6, centery - radarSize - 22, 2 * radarSize + 11, 2 * radarSize + 28, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK)); // <--- radarSize
	}
	Ikaros.m_pDraw->Rectangle(Ikaros.m_pCvars->flRadarPos_x + (radarSize / 2) - 2, Ikaros.m_pCvars->flRadarPos_y + (radarSize / 2) - 2, 5, 5, 1, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK)); // <--- radarSize
	Ikaros.m_pDraw->FillRGBA(Ikaros.m_pCvars->flRadarPos_x + (radarSize / 2) - 1, Ikaros.m_pCvars->flRadarPos_y + (radarSize / 2) - 1, 3, 3, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE)); // <--- radarSize
}

void cRadar::DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, QAngle vAngle, const char* Name, int a, int r, int g, int b)
{
	float dx = vecOriginx.x - vecOriginy.x;
	float dy = vecOriginx.y - vecOriginy.y;
	float flAngle = vAngle.y;
	float yaw = (flAngle) * (M_PI / 180.0);
	float mainViewAngles_CosYaw = cos(yaw);
	float mainViewAngles_SinYaw = sin(yaw);
	float x = dy * (-mainViewAngles_CosYaw) + dx * mainViewAngles_SinYaw;
	float y = dx * (-mainViewAngles_CosYaw) - dy * mainViewAngles_SinYaw;
	float range = radarSize * 25.0f; // <--- radarSize
	if (fabs(x) > range || fabs(y) > range)
	{
		if (y > x)
		{
			if (y > -x) {
				x = range * x / y;
				y = range;
			}
			else {
				y = -range * y / x;
				x = -range;
			}
		}
		else {
			if (y > -x) {
				y = range * y / x;
				x = range;
			}
			else {
				x = -range * x / y;
				y = -range;
			}
		}
	}
	int ScreenX = Ikaros.m_pCvars->flRadarPos_x + (radarSize / 2) + int(x / range * float(radarSize)); // <--- radarSize
	int ScreenY = Ikaros.m_pCvars->flRadarPos_y + (radarSize / 2) + int(y / range * float(radarSize)); // <--- radarSize
	Ikaros.m_pDraw->FillRGBA(ScreenX - 2, ScreenY - 2, 5, 5, RED(CHEAT_BLACK), GREEN(CHEAT_BLACK), BLUE(CHEAT_BLACK), ALPHA(CHEAT_BLACK));
	Ikaros.m_pDraw->FillRGBA(ScreenX - 1, ScreenY - 1, 3, 3, r, g, b, a);
	if (Ikaros.m_pCvars->bRadarName)
		Ikaros.m_pDraw->CenterText(ScreenX + 2, ScreenY + 4, RED(CHEAT_WHITE), GREEN(CHEAT_WHITE), BLUE(CHEAT_WHITE), ALPHA(CHEAT_WHITE), Name);
}