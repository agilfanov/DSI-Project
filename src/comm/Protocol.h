//
// Created by Arthur Gilfanov on 4/22/26.
//

#ifndef DSI_PROJECT_PROTOCOL_H
#define DSI_PROJECT_PROTOCOL_H

enum class MsgTag {
    TERMINATE,
    

};

class Protocol {




    /* Important to, for each tag, implement send and receive versions so handling of it is defined
     *
     * Purpose is so that no code anywhere else writes raw MPI so if protocol changes or new message passing way, change very little
     *
     */

};

#endif //DSI_PROJECT_PROTOCOL_H
