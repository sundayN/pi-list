#include "influx_logger.h"

using namespace influxdb::api;
using namespace ebu_list;
using namespace ebu_list::analysis;
using namespace ebu_list::influx;
using namespace ebu_list::st2110::d20;
using namespace ebu_list::st2110::d21;
using namespace std;

//------------------------------------------------------------------------------

namespace
{
    constexpr auto pcap_stream_id = "ptp";
}

//------------------------------------------------------------------------------

influxdb_ptp_logger::influxdb_ptp_logger(std::string_view url, std::string_view pcap_id)
    : db_(url, pcap_id, pcap_stream_id)
{
}

void influxdb_ptp_logger::on_data(const data_type& info)
{
    const auto offset = std::chrono::duration_cast<std::chrono::nanoseconds>(info.offset_from_master).count();

    db_.send_data("ptp_offset", offset, info.sync_message_timestamp);
}

void influxdb_ptp_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_ptp_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_c_inst_logger::influxdb_c_inst_logger(std::string_view url, std::string_view pcap_id,
                                               std::string_view stream_id)
    : db_(url, pcap_id, stream_id)
{
}

void influxdb_c_inst_logger::on_data(const c_analyzer::packet_info& info)
{
    db_.send_data("cinst", info.cinst, info.packet_time);
}

void influxdb_c_inst_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_c_inst_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_rtp_ts_logger::influxdb_rtp_ts_logger(std::string_view url, std::string_view pcap_id,
                                               std::string_view stream_id)
    : db_(url, pcap_id, stream_id)
{
}

void influxdb_rtp_ts_logger::on_data(const rtp_ts_analyzer::packet_info& info)
{
    db_.send_data("delta_rtp_vs_NTs", from_ticks(info.delta_rtp_vs_NTs), info.timestamp);
    db_.send_data("delta_rtp_vs_packet_time", from_ticks(info.delta_rtp_vs_packet_time), info.timestamp);
    db_.send_data("delta_packet_time_vs_rtp_time_ns", info.delta_packet_time_vs_rtp_time.count(), info.timestamp);
    db_.send_data("delta_previous_rtp_ts", from_ticks(info.rtp_ts_delta), info.timestamp);
}

void influxdb_rtp_ts_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_rtp_ts_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_rtp_logger::influxdb_rtp_logger(std::string_view url, std::string_view pcap_id, std::string_view stream_id)
    : db_(url, pcap_id, stream_id)
{
}

void influxdb_rtp_logger::on_data(const rtp_analyzer::packet_info& info)
{
    db_.send_data("packets_per_frame", info.packets_per_frame, info.timestamp);
}

void influxdb_rtp_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_rtp_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_vrx_logger::influxdb_vrx_logger(std::string_view url, std::string_view pcap_id, std::string_view stream_id,
                                         std::string prefix)
    : db_(url, pcap_id, stream_id), prefix_(std::move(prefix))
{
}

void influxdb_vrx_logger::on_data(const packet_info& fd)
{
    db_.send_data(prefix_ + "-vrx", fd.vrx, fd.packet_time);
    db_.send_data(prefix_ + "-delta_to_ideal_tpr0", fd.delta_to_ideal_tpr0, fd.packet_time);
}

void influxdb_vrx_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_vrx_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_audio_rtp_logger::influxdb_audio_rtp_logger(std::string_view url, std::string_view pcap_id,
                                                     std::string_view stream_id, std::string prefix)
    : db_(url, pcap_id, stream_id), prefix_(std::move(prefix))
{
}

void influxdb_audio_rtp_logger::on_data(const audio_timing_analyser::delay_sample& sample)
{
    db_.send_data(prefix_ + "-pkt-vs-rtp", sample.pkt_ts_vs_rtp_ts, sample.timestamp);
}

void influxdb_audio_rtp_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_audio_rtp_logger::on_error(std::exception_ptr)
{
}

//------------------------------------------------------------------------------

influxdb_audio_tsdf_logger::influxdb_audio_tsdf_logger(std::string_view url, std::string_view pcap_id,
                                                       std::string_view stream_id, std::string prefix)
    : db_(url, pcap_id, stream_id), prefix_(std::move(prefix))
{
}

void influxdb_audio_tsdf_logger::on_data(const audio_timing_analyser::delay_sample& sample)
{
    db_.send_data(prefix_ + "-tsdf", sample.time_stamped_delay_factor, sample.timestamp);
}

void influxdb_audio_tsdf_logger::on_complete()
{
    db_.on_complete();
}

void influxdb_audio_tsdf_logger::on_error(std::exception_ptr)
{
}
