#ifndef CACARUPGRADES_H
#define CACARUPGRADES_H

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <vector>




/** Handler for upgrades ressources
    @author Matthieu Lecesne
*/
class CACarUpgrades
{
public:
    CACarUpgrades();
    ~CACarUpgrades();
    CL_Image getMotor(const int num) const { return motors[num];}
    CL_Image getTires(const int num) const { return tires[num];}
    CL_Image getArmor(const int num) const { return armors[num];}
private:
    std::vector<CL_Image> motors;
    std::vector<CL_Image> tires;
    std::vector<CL_Image> armors;

};

#endif
