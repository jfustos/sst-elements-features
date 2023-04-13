// Copyright 2013-2022 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2013-2022, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// of the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef COMPONENTS_FIREFLY_FUNCSM_TESTANY_H
#define COMPONENTS_FIREFLY_FUNCSM_TESTANY_H

#include "funcSM/api.h"
#include "funcSM/event.h"
#include "ctrlMsg.h"

namespace SST {
namespace Firefly {

class TestanyFuncSM :  public FunctionSMInterface
{
  public:
    SST_ELI_REGISTER_MODULE(
        TestanyFuncSM,
        "firefly",
        "Testany",
        SST_ELI_ELEMENT_VERSION(1,0,0),
        "",
        SST::Firefly::FunctionSMInterface
    )
  public:
    TestanyFuncSM( SST::Params& params );

    virtual void handleStartEvent( SST::Event*, Retval& );
    virtual void handleEnterEvent( Retval& );

    virtual std::string protocolName() { return "CtrlMsgProtocol"; }

  private:
    CtrlMsg::API* proto() { return static_cast<CtrlMsg::API*>(m_proto); }

    TestanyStartEvent* m_event;
};

}
}

#endif
