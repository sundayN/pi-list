#include "ebu/list/st2110/pch.h"
#include "ebu/list/st2110/packets_per_frame_calculator.h"

using namespace ebu_list::st2110;
using namespace ebu_list;

//------------------------------------------------------------------------------
namespace
{
    constexpr int pkt_sequence_max = 0x10000; // 2 ^ 16
}

//------------------------------------------------------------------------------

void packets_per_frame_calculator::on_packet(const rtp::header_lens& header)
{
    if (!header.marker() || count_.has_value()) return;

    if (first_frame_)
    {
        auto current = int(header.sequence_number());
        if (current < first_frame_.value())
        {
            current += pkt_sequence_max;
        }

        count_ = current - first_frame_.value();
    }
    else
    {
        first_frame_ = header.sequence_number();
    }
}

std::optional<int> packets_per_frame_calculator::count() const
{
    return count_;
}
