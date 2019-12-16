/*
* Copyright (C) 2019 Intel Corporation.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice(s),
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice(s),
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
* EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include "Configuration.hpp"
#include "ScenarioWorkload.h"
#include "FunctionCalls.hpp"
#include "AllocationSizes.hpp"
#include "VectorIterator.hpp"
#include "AllocatorFactory.hpp"
#include "Task.hpp"
#include "Numastat.hpp"
#include "CSVLogger.hpp"
#include "TimerSysTime.hpp"
#include "Stats.hpp"

#include <vector>

struct iteration_result {
    bool has_next_memory_operation;
    bool is_allocation_error;
};

class StressIncreaseToMaxDaxKmem
    : public Task
{
public:
    StressIncreaseToMaxDaxKmem(const TaskConf &conf, size_t requested_memory_limit)
        : task_conf(conf),
          req_mem_limit(requested_memory_limit)
    {}

    void run();

    //Return memory operations from the last run.
    std::vector<memory_operation> get_results()
    {
        return results;
    }
    iteration_result get_test_status()
    {
        return test_status;
    }

    static std::vector<iteration_result> execute_test_iterations(
        const TaskConf &task_conf, unsigned time, size_t requested_memory_limit);

private:
    size_t req_mem_limit;
    ScenarioWorkload *scenario_workload;
    std::vector<memory_operation> results;
    const TaskConf &task_conf;

    //Test status
    iteration_result test_status;
};

