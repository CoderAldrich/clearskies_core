/*
 *  This file is part of clearskies_core file synchronization program
 *  Copyright (C) 2014 Pedro Larroy

 *  clearskies_core is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  clearskies_core is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with clearskies_core.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "int_types.h"
#include "message.hpp"
#include <stddef.h>


namespace cs
{
namespace protocol
{

struct PayLoadFound
{
    PayLoadFound():
        found()
        , garbage()
        , size_nl_sz()
        , data_sz()
    {}

    void reset()
    {
        found = false;
        garbage = false;
        size_nl_sz = 0;
        data_sz = 0;
    }
    explicit operator bool() const
    {
        return found;
    }
    size_t total_size() const
    {
        return size_nl_sz + data_sz;
    }
    bool found;
    bool garbage;
    size_t size_nl_sz;
    size_t data_sz;
};

PayLoadFound find_payload(const std::string& buff);



/**
 * @brief Base protocol state class for all protocols
 * @author plarroy
 *
 * Input data is fed and when messages are assembled handle_message is called which implementes the
 * message dispatching logic
 */
class ProtocolState 
{
public:
    /// initial size of the input buffer
    static size_t s_input_buff_size;
    /**
     * feed input data, for example from socket IO
     * Once a full message is read, handle_message is called
     */
    ProtocolState():
          m_input_buff()
        , m_read_payload(false)
        , m_pl_found()
    {
        m_input_buff.reserve(s_input_buff_size);
    }

    //ProtocolState(const ProtocolState&) = delete;
    //ProtocolState& operator=(const ProtocolState&) = delete;

    virtual ~ProtocolState() = default;
    void input(const std::string& s)
    {
        input(s.c_str(), s.size()); 
    }
    void input(const char* data, size_t len);

    virtual void handle_message(const message::Message&) = 0;
    virtual void handle_payload(const char* data, size_t len) = 0;
    virtual void handle_payload_end() = 0;

private:
    /// FIXME: using a deque would be more efficient for appending data
    std::string m_input_buff;

    bool m_read_payload;
    PayLoadFound m_pl_found;
};

struct MsgFound
{
    MsgFound():
        found(false),
        garbage(false),
        prefix(),
        json(),
        signature(),
        end()
    {}
    explicit operator bool() const
    {
        return found;
    }
    bool found;
    bool garbage;
    /// prefix !: payload $: signed &: signed payload
    char prefix;
    std::string json;
    std::string signature;
    /// pos where msg ends, data is processed and destroyed until this pos
    std::string::const_iterator end;
};

MsgFound find_message(const std::string& buff);
} // end ns
} // end ns