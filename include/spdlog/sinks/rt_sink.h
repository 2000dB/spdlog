/*************************************************************************/
/* spdlog - an extremely fast and easy to use c++11 logging library.     */
/* Copyright (c) 2015 Francois Coulombe.                                       */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/


#pragma once

#ifdef RTPRINT

#include <ostream>
#include <mutex>
#include <memory>
#include <rtprint>
#include "../details/null_mutex.h"
#include "./base_sink.h"


namespace spdlog
{
namespace sinks
{
template<class Mutex>
class rt_sink: public base_sink<Mutex>
{
public:
    explicit rt_sink(std::ostream& /*os*/, bool force_flush=false)
    ://_ostream(os),
    _force_flush(force_flush) 
    {
        rt_print_auto_init(1); // initialize rt_print
    }
    rt_sink(const rt_sink&) = delete;
    rt_sink& operator=(const rt_sink&) = delete;
    virtual ~rt_sink() = default;

protected:
    virtual void _sink_it(const details::log_msg& msg) override
    {
        rt_print(msg.formatted.data());
        //((void)__rt_log_print(LoveLevelMapping[msg.level], msg.logger_name.c_str(), msg.formatted.data()));
    }

    //std::ostream& _ostream;
    bool _force_flush;
};

typedef rt_sink<std::mutex> rt_sink_mt;
typedef rt_sink<details::null_mutex> rt_sink_st;
}
}

#endif
