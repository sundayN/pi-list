#pragma once

#include "ebu/list/core/memory/bimo.h"
#include "ebu/list/rtp/listener.h"

namespace ebu_list::analysis
{
    /*
     * Audio TS-DF measurement method:
     * https://tech.ebu.ch/docs/tech/tech3337.pdf
     *
     * Relative Transit Time:
     * D(i,0) = ((R(i) - R(0)) - (S(i) - S(0)))
     * which is equivalent to:
     * D(i,0) = ((R(i) - S(i)) - (R(0)) - S(0)))
     *
     * with:
     * R(0): receive time of the reference packet, the first of measurement
     * window S(0): rtp time of the reference packet R(i): receive time of
     * packet i S(i): rtp time of the packet i
     *
     */
    class audio_timing_analyser : public rtp::listener
    {
      public:
        struct delay_sample
        {
            clock::time_point timestamp;
            int64_t pkt_ts_vs_rtp_ts;
            int64_t time_stamped_delay_factor;
        };

        class listener
        {
          public:
            virtual ~listener() = default;

            virtual void on_data(const delay_sample&)   = 0;
            virtual void on_complete()                  = 0;
            virtual void on_error(std::exception_ptr e) = 0;
        };

        using listener_uptr = std::unique_ptr<listener>;

        audio_timing_analyser(rtp::packet first_packet, listener_uptr listener_rtp_, listener_uptr listener_tsdf,
                              int sampling);
        ~audio_timing_analyser();

        void on_data(const rtp::packet&) override;
        void on_complete() override;
        void on_error(std::exception_ptr ptr) override;

      private:
        struct impl;
        const std::unique_ptr<impl> impl_rtp_;
        const std::unique_ptr<impl> impl_tsdf_;

        int64_t get_delta_pkt_ts_vs_rtp_ts(const rtp::packet& packet);

        int64_t first_packet_ts_usec_;
        int sampling_;
        std::vector<int64_t> delta_pkt_ts_vs_rtp_ts_buffer;
    };
} // namespace ebu_list::analysis
