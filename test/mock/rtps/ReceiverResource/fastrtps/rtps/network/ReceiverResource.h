// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RECEIVER_RESOURCE_H
#define RECEIVER_RESOURCE_H

#include <functional>
#include <vector>
#include <memory>
#include <fastrtps/transport/TransportInterface.h>
#include <fastrtps/rtps/Endpoint.h>

namespace eprosima{
namespace fastrtps{
namespace rtps{

class RTPSWriter;
class RTPSReader;
class MessageReceiver;
class RTPSParticipantImpl;

/**
 * Mock ReceiverResource
 * @ingroup NETWORK_MODULE
 */
class ReceiverResource
{
    friend class NetworkFactory;

public:
    bool SupportsLocator(const Locator_t& localLocator)
    {
        if (LocatorMapsToManagedChannel)
        {
            return LocatorMapsToManagedChannel(localLocator);
        }
        return false;
    }
    void Abort() {}
    ReceiverResource(ReceiverResource&&) {}
    ~ReceiverResource()
    {
        if (Cleanup)
        {
            Cleanup();
        }
    }
    virtual MessageReceiver* CreateMessageReceiver() { return nullptr; }
    void associateEndpoint(Endpoint *) {}
    void removeEndpoint(Endpoint *) {}
    bool checkReaders(EntityId_t) { return false; }
protected:
    ReceiverResource(RTPSParticipantImpl* participant, TransportInterface& transport,
        const Locator_t& locator, uint32_t maxMsgSize)
        : mValid(false)
        , m_participant(participant)
        , m_maxMsgSize(maxMsgSize)
    {
        mValid = transport.OpenInputChannel(locator, this, m_maxMsgSize);
        if (!mValid)
        {
            return;
        }
        Cleanup = [&transport, locator]() { transport.CloseInputChannel(locator); };
        LocatorMapsToManagedChannel = [&transport, locator](const Locator_t& locatorToCheck) -> bool
        { return transport.DoInputLocatorsMatch(locator, locatorToCheck); };
    }

    ReceiverResource() {}
    std::function<void()> Cleanup;
    std::function<bool(const Locator_t&)> LocatorMapsToManagedChannel;
    bool mValid;
    RTPSParticipantImpl* m_participant;
    uint32_t m_maxMsgSize;

private:
    ReceiverResource(const ReceiverResource&) = delete;
    ReceiverResource& operator=(const ReceiverResource&) = delete;
};

} // namespace rtps
} // namespace fastrtps
} // namespace eprosima

#endif
