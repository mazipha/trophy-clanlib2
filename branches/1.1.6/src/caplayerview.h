#ifndef CAPLAYERVIEW_H
#define CAPLAYERVIEW_H

#include "caplayer.h"
#include "cacolor.h"

/** A player view in the panel.
    @author Andrew Mustun
*/
class CAPlayerView {
public:
    CAPlayerView( CAPlayer* player );
    ~CAPlayerView();

    void display( int defaultPos );
    void renderButton();

private:
    //! Pointer to player.

    CAPlayer* player;
    //! The button in players color. Created and destroyed by this class.
    CL_Surface* button;
    /** Current color of this button. Needed for detecting if we must
        re-render the button.
    */
    CAColor currentColor;
};

#endif
