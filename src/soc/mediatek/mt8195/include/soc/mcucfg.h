/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef SOC_MEDIATEK_MT8195_MCUCFG_H
#define SOC_MEDIATEK_MT8195_MCUCFG_H

#include <soc/addressmap.h>
#include <types.h>

struct mt8195_mcucfg_regs {
	u32 rsv_0000[2];
	u32 mbista_mcsi_sf1_con;
	u32 mbista_mcsi_sf1_result;
	u32 mbista_mcsi_sf2_con;
	u32 mbista_mcsi_sf2_result;
	u32 mbista_etb_con;
	u32 mbista_etb_result;
	u32 mbista_rstb;
	u32 mbista_all_result;
	u32 rsv_0028[2];
	u32 mbist_trigger_mux_ctl;
	u32 rsv_0034[3];
	u32 dfd_ctrl;
	u32 dfd_cnt_l;
	u32 dfd_cnt_h;
	u32 rsv_004c[5];
	u32 mp_top_dbg_mon_sel;
	u32 mp_top_dbg_mon;
	u32 mp0_dbg_mon_sel;
	u32 mp0_dbg_mon;
	u32 rsv_0070[28];
	u32 mp0_ptp_sensor_sel;
	u32 emi_addr_wrap_cfg;
	u32 emi_addr_wrap_state;
	u32 rsv_00ec[3];
	u32 armpll_jit_clk_out_sel;
	u32 rsv_00fc;
	u32 cci_tra_cfg0;
	u32 rsv_0104[4];
	u32 cci_tra_cfg5;
	u32 cci_tra_cfg6;
	u32 cci_tra_cfg7;
	u32 cci_tra_cfg8;
	u32 cci_tra_cfg9;
	u32 cci_tra_cfg10;
	u32 cci_tra_cfg11;
	u32 cci_tra_cfg12;
	u32 rsv_0134[51];
	u32 cci_m0_tra;
	u32 cci_m1_tra;
	u32 cci_m2_tra;
	u32 rsv_020c[5];
	u32 cci_s1_tra;
	u32 cci_s2_tra;
	u32 cci_s3_tra;
	u32 cci_s4_tra;
	u32 rsv_0230[4];
	u32 cci_m0_tra_latch;
	u32 cci_m1_tra_latch;
	u32 cci_m2_tra_latch;
	u32 rsv_024c[5];
	u32 cci_s1_tra_latch;
	u32 cci_s2_tra_latch;
	u32 cci_s3_tra_latch;
	u32 cci_s4_tra_latch;
	u32 rsv_0270[20];
	u32 cci_m0_if;
	u32 cci_m1_if;
	u32 cci_m2_if;
	u32 rsv_02cc[5];
	u32 cci_s1_if;
	u32 cci_s2_if;
	u32 cci_s3_if;
	u32 cci_s4_if;
	u32 rsv_02f0[12];
	u32 cci_m0_if_latch;
	u32 cci_m1_if_latch;
	u32 cci_m2_if_latch;
	u32 rsv_032c[5];
	u32 cci_s1_if_latch;
	u32 cci_s2_if_latch;
	u32 cci_s3_if_latch;
	u32 cci_s4_if_latch;
	u32 rsv_0350[44];
	u32 l3c_share_status0;
	u32 l3c_share_status1;
	u32 l3c_share_status2;
	u32 rsv_040c;
	u32 mp0_cpu0_dc_age;
	u32 mp0_cpu1_dc_age;
	u32 mp0_cpu2_dc_age;
	u32 mp0_cpu3_dc_age;
	u32 mp0_cpu4_dc_age;
	u32 mp0_cpu5_dc_age;
	u32 mp0_cpu6_dc_age;
	u32 mp0_cpu7_dc_age;
	u32 rsv_0430[52];
	u32 mp0_cpu0_nonwfx_ctrl;
	u32 mp0_cpu0_nonwfx_cnt;
	u32 mp0_cpu1_nonwfx_ctrl;
	u32 mp0_cpu1_nonwfx_cnt;
	u32 mp0_cpu2_nonwfx_ctrl;
	u32 mp0_cpu2_nonwfx_cnt;
	u32 mp0_cpu3_nonwfx_ctrl;
	u32 mp0_cpu3_nonwfx_cnt;
	u32 mp0_cpu4_nonwfx_ctrl;
	u32 mp0_cpu4_nonwfx_cnt;
	u32 mp0_cpu5_nonwfx_ctrl;
	u32 mp0_cpu5_nonwfx_cnt;
	u32 mp0_cpu6_nonwfx_ctrl;
	u32 mp0_cpu6_nonwfx_cnt;
	u32 mp0_cpu7_nonwfx_ctrl;
	u32 mp0_cpu7_nonwfx_cnt;
	u32 rsv_0540[48];
	u32 mp0_ses_apb_trig;
	u32 mp0_ses_clk_en;
	u32 rsv_0608[2];
	u32 wfx_ret_met_dbc_sel;
	u32 rsv_0614[3];
	u32 adb_bist_cfg1;
	u32 adb_bist_cfg2_md;
	u32 adb_bist_cfg3_go;
	u32 adb_bist_done;
	u32 adb_bist_pass;
	u32 adb_bist_done1;
	u32 rsv_0638;
	u32 adb_bist_pass1;
	u32 rsv_0640[48];
	u32 axi2acp_cfg_ctrl;
	u32 axi2acp_cfg_mask_id;
	u32 rsv_0708[2];
	u32 axi2acp_ar_def_set;
	u32 rsv_0714;
	u32 axi2acp_aw_def_set;
	u32 rsv_071c;
	u32 axi2acp_err_addr0;
	u32 axi2acp_err_addr1;
	u32 axi2acp_err_st;
	u32 axi2acp_err_id;
	u32 axi2acp_err_irq;
	u32 axi2acp_err_dbgout;
	u32 rsv_0738[50];
	u32 mst_ccim0_inject_fault;
	u32 mst_ccim0_rec_par;
	u32 mst_ccim0_log_rid;
	u32 rsv_080c;
	u32 mst_ccim0_log_rd0;
	u32 mst_ccim0_log_rd1;
	u32 mst_ccim0_log_rd2;
	u32 mst_ccim0_log_rd3;
	u32 mst_ccim1_inject_fault;
	u32 mst_ccim1_rec_par;
	u32 mst_ccim1_log_rid;
	u32 rsv_082c;
	u32 mst_ccim1_log_rd0;
	u32 mst_ccim1_log_rd1;
	u32 mst_ccim1_log_rd2;
	u32 mst_ccim1_log_rd3;
	u32 mst_intaxi_inject_fault;
	u32 mst_intaxi_rec_par;
	u32 mst_intaxi_log_rid;
	u32 rsv_084c;
	u32 mst_intaxi_log_rd0;
	u32 mst_intaxi_log_rd1;
	u32 rsv_0858[2];
	u32 slv_1to2_inject_fault;
	u32 slv_1to2_rec_par;
	u32 slv_1to2_log_awid;
	u32 slv_1to2_log_arid;
	u32 slv_1to2_log_awa0;
	u32 slv_1to2_log_awa1;
	u32 slv_1to2_log_ara0;
	u32 slv_1to2_log_ara1;
	u32 slv_1to2_log_wid;
	u32 rsv_0884[3];
	u32 slv_1to2_log_wd0;
	u32 slv_1to2_log_wd1;
	u32 slv_1to2_log_wd2;
	u32 slv_1to2_log_wd3;
	u32 slv_l3c_inject_fault;
	u32 slv_l3c_rec_par;
	u32 slv_l3c_log_awid;
	u32 slv_l3c_log_arid;
	u32 slv_l3c_log_awa0;
	u32 slv_l3c_log_awa1;
	u32 slv_l3c_log_ara0;
	u32 slv_l3c_log_ara1;
	u32 slv_l3c_log_wid;
	u32 rsv_08c4;
	u32 slv_l3c_log_wd0;
	u32 slv_l3c_log_wd1;
	u32 slv_gic_inject_fault;
	u32 slv_gic_rec_par;
	u32 slv_gic_log_awid;
	u32 slv_gic_log_arid;
	u32 slv_gic_log_awa0;
	u32 slv_gic_log_awa1;
	u32 slv_gic_log_ara0;
	u32 slv_gic_log_ara1;
	u32 slv_gic_log_wid;
	u32 rsv_08f4;
	u32 slv_gic_log_wd0;
	u32 slv_gic_log_wd1;
	u32 rsv_0900[64];
	u32 ildo_vin_big0;
	u32 ildo_out_big0;
	u32 ildo_ovstck_big0;
	u32 ildo_vo2hck_big0;
	u32 ildo_mhstck_big0;
	u32 ildo_mlstck_big0;
	u32 ilod_uvwin_big0;
	u32 ilod_ovwin_big0;
	u32 ildo_pd_cfg_big0;
	u32 rsv_0a24[3];
	u32 ildo_vin_big1;
	u32 ildo_out_big1;
	u32 ildo_ovstck_big1;
	u32 ildo_vo2hck_big1;
	u32 ildo_mhstck_big1;
	u32 ildo_mlstck_big1;
	u32 ilod_uvwin_big1;
	u32 ilod_ovwin_big1;
	u32 ildo_pd_cfg_big1;
	u32 rsv_0a54[3];
	u32 ildo_vin_big2;
	u32 ildo_out_big2;
	u32 ildo_ovstck_big2;
	u32 ildo_vo2hck_big2;
	u32 ildo_mhstck_big2;
	u32 ildo_mlstck_big2;
	u32 ilod_uvwin_big2;
	u32 ilod_ovwin_big2;
	u32 ildo_pd_cfg_big2;
	u32 rsv_0a84[3];
	u32 ildo_vin_big3;
	u32 ildo_out_big3;
	u32 ildo_ovstck_big3;
	u32 ildo_vo2hck_big3;
	u32 ildo_mhstck_big3;
	u32 ildo_mlstck_big3;
	u32 ilod_uvwin_big3;
	u32 ilod_ovwin_big3;
	u32 ildo_pd_cfg_big3;
	u32 rsv_0ab4[1495];
	u32 l3c_share_cfg0;
	u32 l3c_share_cfg1;
	u32 l3c_share_cfg2;
	u32 rsv_221c;
	u32 udi_cfg0;
	u32 udi_cfg1;
	u32 rsv_2228[2];
	u32 mcusys_core_status;
	u32 rsv_2234;
	u32 cfg_sys_valid;
	u32 cfg_sysbase_addr_0;
	u32 cfg_sysbase_addr_1;
	u32 cfg_sysbase_addr_2;
	u32 cfg_sysbase_addr_3;
	u32 cfg_sysbase_addr_4;
	u32 rsv_2250[4];
	u32 mcusys_base;
	u32 l3c_sram_base;
	u32 gic_periph_base;
	u32 cci_periph_base;
	u32 cci_periph_infra_base;
	u32 dfd_sram_base;
	u32 l3c_mm_sram_base;
	u32 ext_l3c_sram_base;
	u32 ext_gic_periph_base;
	u32 mcusys_qos_shaper_degree;
	u32 mcusys_qos_shaper_others;
	u32 mcusys_qos_age_set_enable;
	u32 sspm_cpueb_turbo_pll_ctl;
	u32 cpu_eb_apb_base;
	u32 cpu_eb_tcm_btb_delsel;
	u32 cpu_eb_mem_misc;
	u32 cpu_plldiv_cfg0;
	u32 cpu_plldiv_cfg1;
	u32 rsv_22a8[14];
	u32 bus_plldiv_cfg;
	u32 rsv_22e4[3];
	u32 plldiv_ctl0;
	u32 cpuplldiv_unictl;
	u32 rsv_22f8[2];
	u32 mcsi_ram_delsel0;
	u32 mcsi_ram_delsel1;
	u32 rsv_2308[7];
	u32 mbist_delsel_fuse_dis;
	u32 mbist_delsel_magic_key;
	u32 rsv_232c[21];
	u32 etb_cfg0;
	u32 rsv_2384[3];
	u32 bus_parity_gen_en;
	u32 bus_parity_clr;
	u32 bus_parity_chk_en;
	u32 bus_parity_fail;
	u32 dsu2biu_addr_remap_cfg;
	u32 dsu2biu_addr_remap_sta;
	u32 rsv_23a8[2];
	u32 dsu2biu_addr_remap_0_cfg0;
	u32 dsu2biu_addr_remap_0_cfg1;
	u32 dsu2biu_addr_remap_0_cfg2;
	u32 rsv_23bc;
	u32 dsu2biu_addr_remap_1_cfg0;
	u32 dsu2biu_addr_remap_1_cfg1;
	u32 dsu2biu_addr_remap_1_cfg2;
	u32 rsv_23cc;
	u32 dsu2biu_addr_remap_magic;
	u32 rsv_23d4[11];
	u32 cci_rgu;
	u32 rsv_2404[3];
	u32 mcsi_cfg0;
	u32 mcsi_cfg1;
	u32 mcsi_cfg2;
	u32 mcsi_cfg3;
	u32 mcsi_cfg4;
	u32 rsv_2424[7];
	u32 mcsic_dcm0;
	u32 mcsic_dcm1;
	u32 rsv_2448[18];
	u32 apmcu2emi_early_cke_ctl0;
	u32 apmcu2emi_early_cke_ctl1;
	u32 apmcu2emi_early_ebg_ctl0;
	u32 apmcu2emi_early_ebg_ctl1;
	u32 apmcu2emi_early_ebg_ctl2;
	u32 apmcu2emi_early_ebg_ctl3;
	u32 apmcu2emi_early_ebg_ctl4;
	u32 apmcu2emi_early_ebg_ctl5;
	u32 apmcu2emi_early_ebg_enable01;
	u32 apmcu2emi_early_ebg_enable23;
	u32 emi_hash_violation;
	u32 emi_interleave_update_mask;
	u32 rsv_24c0[16];
	u32 mp_adb_dcm_cfg0;
	u32 rsv_2504;
	u32 mp_adb_dcm_cfg2;
	u32 rsv_250c;
	u32 mp_adb_dcm_cfg4;
	u32 rsv_2514;
	u32 mp_misc_dcm_cfg0;
	u32 rsv_251c[9];
	u32 etb_ck_ctl;
	u32 rsv_2544[15];
	u32 dcc_cpu_con0;
	u32 dcc_cpu_con1;
	u32 rsv_2588[6];
	u32 dcc_bus_con0;
	u32 rsv_25a4[7];
	u32 mcusys_dcm_cfg0;
	u32 rsv_25c4[79];
	u32 fcm_spmc_sw_cfg1;
	u32 fcm_spmc_sw_cfg2;
	u32 fcm_spmc_wait_cfg;
	u32 fcm_spmc_sw_pchannel;
	u32 fcm_spmc_pwr_status;
	u32 fcm_spmc_off_thres;
	u32 fcm_spmc_wdt_latch_info;
	u32 rsv_271c[9];
	u32 mcusys_spmc_sw_cfg;
	u32 mcusys_spmc_wait_cfg;
	u32 mcusys_spmc_pwr_status;
	u32 rsv_274c[45];
	u32 cpc_pllbuck_req_ctrl;
	u32 mcusys_pwr_ctrl;
	u32 cpusys_pwr_ctrl;
	u32 sw_gic_wakeup_req;
	u32 cpc_pllbuck_arb_weight;
	u32 cpc_flow_ctrl_cfg;
	u32 cpc_last_core_req;
	u32 cpc_cpusys_last_core_resp;
	u32 rsv_2820;
	u32 cpc_mcusys_last_core_resp;
	u32 cpc_pwr_on_mask;
	u32 rsv_282c[5];
	u32 cpc_spmc_pwr_status;
	u32 cpc_core_cur_fsm;
	u32 cpc_cpusys_mcusys_cur_fsm;
	u32 cpc_wakeup_req;
	u32 rsv_2850;
	u32 cpc_gp0_gp1_status;
	u32 rsv_2858;
	u32 cpc_turbo_ctrl;
	u32 cpc_turbo_gp0_ctrl;
	u32 cpc_turbo_gp1_ctrl;
	u32 cpc_turbo_gp2_ctrl;
	u32 cpc_turbo_pwr_on_mask;
	u32 cpc_turbo_gp0_req;
	u32 cpc_turbo_gp1_req;
	u32 cpc_turbo_gp2_req;
	u32 rsv_287c;
	u32 cpc_turbo_gp0_resp;
	u32 cpc_turbo_gp1_resp;
	u32 cpc_turbo_gp2_resp;
	u32 cpc_coh_block_thres;
	u32 cpc_int_status;
	u32 cpc_int_enable;
	u32 pllbuck_group_func;
	u32 cpc_dcm_enable;
	u32 cpc_pllbuck_state;
	u32 cpc_cpu_on_sw_hint;
	u32 cpc_cpu_on_sw_hint_set;
	u32 cpc_cpu_on_sw_hint_clear;
	u32 rsv_28b0[20];
	u32 emi_wfifo;
	u32 axi1to4_cfg;
	u32 apb_cfg;
	u32 emi_adb_edge_sel;
	u32 rsv_2910[4];
	u32 sclk_cfg_slow_down_ck;
	u32 rsv_2924[3];
	u32 acpwakeup;
	u32 rsv_2934;
	u32 l3gic_idle_bypass;
	u32 rsv_293c[21];
	u32 mcusys_dbg_mon_sel;
	u32 mcusys_dbg_mon;
	u32 rsv_2998[27];
	u32 lkg_mon_sw;
	u32 lkg_mon_en;
	u32 rsv_2a0c[29];
	u32 gic_acao_ctl0;
	u32 rsv_2a84;
	u32 gic_acao_ctl2;
	u32 rsv_2a8c[29];
	u32 spmc_dbg_setting;
	u32 kernel_base_l;
	u32 kernel_base_h;
	u32 systime_base_l;
	u32 systime_base_h;
	u32 trace_data_selection;
	u32 rsv_2b18[2];
	u32 trace_data_entry0_l;
	u32 trace_data_entry0_h;
	u32 trace_data_entry1_l;
	u32 trace_data_entry1_h;
	u32 trace_data_entry2_l;
	u32 trace_data_entry2_h;
	u32 trace_data_entry3_l;
	u32 trace_data_entry3_h;
	u32 cpu0_on_off_latency;
	u32 cpu1_on_off_latency;
	u32 cpu2_on_off_latency;
	u32 cpu3_on_off_latency;
	u32 cpu4_on_off_latency;
	u32 cpu5_on_off_latency;
	u32 cpu6_on_off_latency;
	u32 cpu7_on_off_latency;
	u32 cluster_off_latency;
	u32 cluster_on_latency;
	u32 mcusys_on_off_latency;
	u32 rsv_2b6c;
	u32 cluster_off_dormant_counter;
	u32 cluster_off_dormant_counter_clear;
	u32 turbo_gp0_gp1_latency;
	u32 turbo_gp2_latency;
	u32 cpc_wdt_latch_info1;
	u32 cpc_wdt_latch_info2;
	u32 cpc_wdt_latch_info3;
	u32 cpc_wdt_latch_info4;
	u32 cpc_wdt_latch_info5;
	u32 cpc_pmu_ctrl;
	u32 cpc_pmu_cnt_clr;
	u32 cpc_pmu_cnt0;
	u32 rsv_2ba0[4];
	u32 cpc_wdt_latch_info6;
	u32 cpc_wdt_latch_info7;
	u32 cpc_ptm_event_en_ctrl;
	u32 cpc_ptm_event_en_ctrl1;
	u32 cpc_ptm_trace_sel;
	u32 cpc_ptm_trace_status_l;
	u32 cpc_ptm_trace_status_h;
	u32 rsv_2bcc[29];
	u32 sesv6_bg_ctrl;
	u32 rsv_2c44[3];
	u32 dsu_sesv6_ao_reg0;
	u32 dsu_sesv6_ao_reg1;
	u32 dsu_sesv6_ao_reg2;
	u32 dsu_sesv6_ao_reg3;
	u32 dsu_sesv6_ao_reg4;
	u32 rsv_2c64[39];
	u32 ildo_dout_sel;
	u32 rsv_2d04[31];
	u32 dreq20_little_en;
	u32 rsv_2d84[2];
	u32 dreq20_big_vproc_iso;
	u32 rsv_2d90[28];
	u32 pikachu_event;
	u32 pikachu_status;
	u32 rsv_2e08[126];
	u32 cpu0_drcc_ao_config;
	u32 rsv_3004[3];
	u32 cpu0_sesv6_ao_reg0;
	u32 cpu0_sesv6_ao_reg1;
	u32 cpu0_sesv6_ao_reg2;
	u32 cpu0_sesv6_ao_reg3;
	u32 cpu0_sesv6_ao_reg4;
	u32 rsv_3024[7];
	u32 cpu0_dfs_cfg;
	u32 rsv_3044[3];
	u32 cpu0_turbo_cfg;
	u32 rsv_3054[105];
	u32 cpu0_resereved_reg;
	u32 cpu0_resereved_reg_rd;
	u32 cpu1_drcc_ao_config;
	u32 rsv_3204[3];
	u32 cpu1_sesv6_ao_reg0;
	u32 cpu1_sesv6_ao_reg1;
	u32 cpu1_sesv6_ao_reg2;
	u32 cpu1_sesv6_ao_reg3;
	u32 cpu1_sesv6_ao_reg4;
	u32 rsv_3224[7];
	u32 cpu1_dfs_cfg;
	u32 rsv_3244[3];
	u32 cpu1_turbo_cfg;
	u32 rsv_3254[105];
	u32 cpu1_resereved_reg;
	u32 cpu1_resereved_reg_rd;
	u32 cpu2_drcc_ao_config;
	u32 rsv_3404[3];
	u32 cpu2_sesv6_ao_reg0;
	u32 cpu2_sesv6_ao_reg1;
	u32 cpu2_sesv6_ao_reg2;
	u32 cpu2_sesv6_ao_reg3;
	u32 cpu2_sesv6_ao_reg4;
	u32 rsv_3424[7];
	u32 cpu2_dfs_cfg;
	u32 rsv_3444[3];
	u32 cpu2_turbo_cfg;
	u32 rsv_3454[105];
	u32 cpu2_resereved_reg;
	u32 cpu2_resereved_reg_rd;
	u32 cpu3_drcc_ao_config;
	u32 rsv_3604[3];
	u32 cpu3_sesv6_ao_reg0;
	u32 cpu3_sesv6_ao_reg1;
	u32 cpu3_sesv6_ao_reg2;
	u32 cpu3_sesv6_ao_reg3;
	u32 cpu3_sesv6_ao_reg4;
	u32 rsv_3624[7];
	u32 cpu3_dfs_cfg;
	u32 rsv_3644[3];
	u32 cpu3_turbo_cfg;
	u32 rsv_3654[105];
	u32 cpu3_resereved_reg;
	u32 cpu3_resereved_reg_rd;
	u32 cpu4_drcc_ao_config;
	u32 rsv_3804[3];
	u32 cpu4_sesv6_ao_reg0;
	u32 cpu4_sesv6_ao_reg1;
	u32 cpu4_sesv6_ao_reg2;
	u32 cpu4_sesv6_ao_reg3;
	u32 cpu4_sesv6_ao_reg4;
	u32 rsv_3824[3];
	u32 cpu4_didt_reg;
	u32 rsv_3834[3];
	u32 cpu4_dfs_cfg;
	u32 rsv_3844[3];
	u32 cpu4_turbo_cfg;
	u32 rsv_3854[105];
	u32 cpu4_resereved_reg;
	u32 cpu4_resereved_reg_rd;
	u32 cpu5_drcc_ao_config;
	u32 rsv_3a04[3];
	u32 cpu5_sesv6_ao_reg0;
	u32 cpu5_sesv6_ao_reg1;
	u32 cpu5_sesv6_ao_reg2;
	u32 cpu5_sesv6_ao_reg3;
	u32 cpu5_sesv6_ao_reg4;
	u32 rsv_3a24[3];
	u32 cpu5_didt_reg;
	u32 rsv_3a34[3];
	u32 cpu5_dfs_cfg;
	u32 rsv_3a44[3];
	u32 cpu5_turbo_cfg;
	u32 rsv_3a54[105];
	u32 cpu5_resereved_reg;
	u32 cpu5_resereved_reg_rd;
	u32 cpu6_drcc_ao_config;
	u32 rsv_3c04[3];
	u32 cpu6_sesv6_ao_reg0;
	u32 cpu6_sesv6_ao_reg1;
	u32 cpu6_sesv6_ao_reg2;
	u32 cpu6_sesv6_ao_reg3;
	u32 cpu6_sesv6_ao_reg4;
	u32 rsv_3c24[3];
	u32 cpu6_didt_reg;
	u32 cpu6_mem_lre_reg;
	u32 rsv_3c38[2];
	u32 cpu6_dfs_cfg;
	u32 rsv_3c44[3];
	u32 cpu6_turbo_cfg;
	u32 rsv_3c54[105];
	u32 cpu6_resereved_reg;
	u32 cpu6_resereved_reg_rd;
	u32 cpu7_drcc_ao_config;
	u32 rsv_3e04[3];
	u32 cpu7_sesv6_ao_reg0;
	u32 cpu7_sesv6_ao_reg1;
	u32 cpu7_sesv6_ao_reg2;
	u32 cpu7_sesv6_ao_reg3;
	u32 cpu7_sesv6_ao_reg4;
	u32 rsv_3e24[3];
	u32 cpu7_didt_reg;
	u32 cpu7_mem_lre_reg;
	u32 rsv_3e38[2];
	u32 cpu7_dfs_cfg;
	u32 rsv_3e44[3];
	u32 cpu7_turbo_cfg;
	u32 rsv_3e54[105];
	u32 cpu7_resereved_reg;
	u32 cpu7_resereved_reg_rd;
	u32 rsv_4000[512];
	u32 mp0_mbist_cfg;
	u32 rsv_4804[15];
	u32 mp0_l3_data_ram_delsel;
	u32 mp0_l3_tag_ram_delsel;
	u32 mp0_l3_victim_ram_delsel;
	u32 mp0_l3_scu_sf_ram_delsel;
	u32 rsv_4850[12];
	u32 mp0_dcm_cfg0;
	u32 mp0_dcm_cfg1;
	u32 mp0_dcm_cfg2;
	u32 mp0_dcm_cfg3;
	u32 mp0_dcm_cfg4;
	u32 mp0_dcm_cfg5;
	u32 mp0_dcm_cfg6;
	u32 mp0_dcm_cfg7;
	u32 mp0_dcm_cfg8;
	u32 rsv_48a4[7];
	u32 mp0_l3_cache_parity1;
	u32 mp0_l3_cache_parity2;
	u32 mp0_l3_cache_parity3;
	u32 rsv_48cc;
	u32 mp0_cluster_cfg0;
	u32 rsv_48d4[3];
	u32 mp0_cluster_cfg4;
	u32 mp0_cluster_cfg5;
	u32 mp0_cluster_cfg6;
	u32 mp0_cluster_cfg7;
	u32 rsv_48f0[4];
	u32 mp0_cluster_cfg8;
	u32 mp0_cluster_cfg9;
	u32 mp0_cluster_cfg10;
	u32 mp0_cluster_cfg11;
	u32 mp0_cluster_cfg12;
	u32 mp0_cluster_cfg13;
	u32 mp0_cluster_cfg14;
	u32 mp0_cluster_cfg15;
	u32 mp0_cluster_cfg16;
	u32 mp0_cluster_cfg17;
	u32 mp0_cluster_cfg18;
	u32 mp0_cluster_cfg19;
	u32 mp0_cluster_cfg20;
	u32 mp0_cluster_cfg21;
	u32 mp0_cluster_cfg22;
	u32 mp0_cluster_cfg23;
	u32 mp0_mem_dreq_cfg;
	u32 mp0_victim_rd_mask;
	u32 mp0_minidcc_enable;
	u32 mp0_mem_lv_mode;
	u32 rsv_4950[172];
	u32 cpu_type0_spmc0_cfg;
	u32 rsv_4c04[7];
	u32 cpu_type0_ram_delsel0_cfg;
	u32 cpu_type0_ram_delsel1_cfg;
	u32 cpu_type0_ram_delsel2_cfg;
	u32 cpu_type0_ram_delsel3_cfg;
	u32 rsv_4c30[52];
	u32 cpu_type1_spmc0_cfg;
	u32 rsv_4d04[3];
	u32 cpu_type1_mpmmen;
	u32 cpu_ppmctl;
	u32 cpu_typex_most_on_mode;
	u32 rsv_4d1c;
	u32 cpu_type1_ram_delsel0_cfg;
	u32 cpu_type1_ram_delsel1_cfg;
	u32 cpu_type1_ram_delsel2_cfg;
	u32 cpu_type1_ram_delsel3_cfg;
	u32 rsv_4d30[4];
	u32 cpu_type1_drss_cfg0;
	u32 cpu_type1_drss_cfg1;
	u32 rsv_4d48[54];
	u32 cpu_type2_ram_delsel0_cfg;
	u32 cpu_type2_ram_delsel1_cfg;
	u32 cpu_type2_ram_delsel2_cfg;
	u32 cpu_type2_ram_delsel3_cfg;
	u32 rsv_4e30[244];
	u32 mcusys_pwr_con;
	u32 mp0_cputop_pwr_con;
	u32 mp0_cpu0_pwr_con;
	u32 mp0_cpu1_pwr_con;
	u32 mp0_cpu2_pwr_con;
	u32 mp0_cpu3_pwr_con;
	u32 mp0_cpu4_pwr_con;
	u32 mp0_cpu5_pwr_con;
	u32 mp0_cpu6_pwr_con;
	u32 mp0_cpu7_pwr_con;
	u32 rsv_5228[246];
	u32 sec_pol_ctl_en0;
	u32 sec_pol_ctl_en1;
	u32 sec_pol_ctl_en2;
	u32 sec_pol_ctl_en3;
	u32 sec_pol_ctl_en4;
	u32 sec_pol_ctl_en5;
	u32 sec_pol_ctl_en6;
	u32 sec_pol_ctl_en7;
	u32 sec_pol_ctl_en8;
	u32 sec_pol_ctl_en9;
	u32 sec_pol_ctl_en10;
	u32 sec_pol_ctl_en11;
	u32 sec_pol_ctl_en12;
	u32 sec_pol_ctl_en13;
	u32 sec_pol_ctl_en14;
	u32 sec_pol_ctl_en15;
	u32 sec_pol_ctl_en16;
	u32 sec_pol_ctl_en17;
	u32 sec_pol_ctl_en18;
	u32 sec_pol_ctl_en19;
	u32 sec_pol_ctl_en20;
	u32 sec_pol_ctl_en21;
	u32 sec_pol_ctl_en22;
	u32 sec_pol_ctl_en23;
	u32 sec_pol_ctl_en24;
	u32 sec_pol_ctl_en25;
	u32 sec_pol_ctl_en26;
	u32 sec_pol_ctl_en27;
	u32 sec_pol_ctl_en28;
	u32 sec_pol_ctl_en29;
	u32 sec_pol_ctl_en30;
	u32 sec_pol_ctl_en31;
	u32 int_pol_ctl0;
	u32 int_pol_ctl1;
	u32 int_pol_ctl2;
	u32 int_pol_ctl3;
	u32 int_pol_ctl4;
	u32 int_pol_ctl5;
	u32 int_pol_ctl6;
	u32 int_pol_ctl7;
	u32 int_pol_ctl8;
	u32 int_pol_ctl9;
	u32 int_pol_ctl10;
	u32 int_pol_ctl11;
	u32 int_pol_ctl12;
	u32 int_pol_ctl13;
	u32 int_pol_ctl14;
	u32 int_pol_ctl15;
	u32 int_pol_ctl16;
	u32 int_pol_ctl17;
	u32 int_pol_ctl18;
	u32 int_pol_ctl19;
	u32 int_pol_ctl20;
	u32 int_pol_ctl21;
	u32 int_pol_ctl22;
	u32 int_pol_ctl23;
	u32 int_pol_ctl24;
	u32 int_pol_ctl25;
	u32 int_pol_ctl26;
	u32 int_pol_ctl27;
	u32 int_pol_ctl28;
	u32 int_pol_ctl29;
	u32 int_pol_ctl30;
	u32 int_pol_ctl31;
	u32 int_msk_ctl0;
	u32 int_msk_ctl1;
	u32 int_msk_ctl2;
	u32 int_msk_ctl3;
	u32 int_msk_ctl4;
	u32 int_msk_ctl5;
	u32 int_msk_ctl6;
	u32 int_msk_ctl7;
	u32 int_msk_ctl8;
	u32 int_msk_ctl9;
	u32 int_msk_ctl10;
	u32 int_msk_ctl11;
	u32 int_msk_ctl12;
	u32 int_msk_ctl13;
	u32 int_msk_ctl14;
	u32 int_msk_ctl15;
	u32 int_msk_ctl16;
	u32 int_msk_ctl17;
	u32 int_msk_ctl18;
	u32 int_msk_ctl19;
	u32 int_msk_ctl20;
	u32 int_msk_ctl21;
	u32 int_msk_ctl22;
	u32 int_msk_ctl23;
	u32 int_msk_ctl24;
	u32 int_msk_ctl25;
	u32 int_msk_ctl26;
	u32 int_msk_ctl27;
	u32 int_msk_ctl28;
	u32 int_msk_ctl29;
	u32 int_msk_ctl30;
	u32 int_msk_ctl31;
	u32 int_msk_ctl_all;
	u32 int_cfg_indirect_access;
	u32 int_cfg_direct_access_en;
	u32 rsv_578c[557];
	u32 dfd_internal_ctl;
	u32 dfd_internal_counter;
	u32 dfd_internal_pwr_on;
	u32 dfd_internal_chain_legth_0;
	u32 dfd_internal_shift_clk_ratio;
	u32 dfd_internal_counter_return;
	u32 dfd_internal_sram_access;
	u32 dfd_finish_wait_time;
	u32 dfd_internal_chain_group;
	u32 dfd_internal_chain_inv_info_ll;
	u32 dfd_internal_chain_inv_info_lh;
	u32 dfd_internal_chain_inv_info_hl;
	u32 dfd_internal_chain_inv_info_hh;
	u32 dfd_internal_test_so_over_64;
	u32 dfd_internal_mask_out;
	u32 dfd_internal_sw_ns_trigger;
	u32 dfd_internal_mcsi;
	u32 dfd_internal_mcsi_sel_status;
	u32 dfd_v30_ctl;
	u32 dfd_v30_base_addr;
	u32 dfd_power_ctl;
	u32 dfd_reset_on;
	u32 dfd_test_si_0;
	u32 dfd_test_si_1;
	u32 dfd_status_clean;
	u32 dfd_status_return;
	u32 dfd_v35_enable;
	u32 dfd_v35_tap_number;
	u32 dfd_v35_tap_en;
	u32 dfd_v35_ctl;
	u32 dfd_v35_tap_seq0;
	u32 dfd_v35_tap_seq1;
	u32 dfd_v35_seq0_0;
	u32 dfd_v35_seq0_1;
	u32 dfd_v35_seq1_0;
	u32 dfd_v35_seq1_1;
	u32 dfd_v35_seq2_0;
	u32 dfd_v35_seq2_1;
	u32 rsv_60d8[6];
	u32 dfd_soc_clock_stop_mask;
	u32 rsv_60f4[2];
	u32 dfd_hw_trigger_mask;
	u32 dfd_v50_enable;
	u32 dfd_v50_self_trigger_iteration;
	u32 dfd_v50_start_trigger;
	u32 dfd_v50_cpuck_halt;
	u32 dfd_v50_26m_resume;
	u32 dfd_v50_26m_halt_release;
	u32 dfd_v50_system_halt_time;
	u32 dfd_v50_group_0_1_diff;
	u32 dfd_v50_group_0_2_diff;
	u32 dfd_v50_group_0_3_diff;
	u32 dfd_v50_group_0_4_diff;
	u32 dfd_v50_group_0_5_diff;
	u32 dfd_v50_group_0_6_diff;
	u32 dfd_v50_group_0_7_diff;
	u32 dfd_v50_group_0_8_diff;
	u32 dfd_v50_group_0_9_diff;
	u32 dfd_v50_group_0_10_diff;
	u32 dfd_v50_group_0_11_diff;
	u32 dfd_v50_group_0_12_diff;
	u32 dfd_v50_group_0_13_diff;
	u32 dfd_v50_group_0_14_diff;
	u32 dfd_v50_group_0_15_diff;
	u32 dfd_v50_group_0_16_diff;
	u32 dfd_v50_group_0_17_diff;
	u32 dfd_v50_group_0_18_diff;
	u32 dfd_v50_group_0_19_diff;
	u32 dfd_v50_group_0_20_diff;
	u32 dfd_v50_group_0_21_diff;
	u32 dfd_v50_group_0_22_diff;
	u32 dfd_v50_group_0_23_diff;
	u32 dfd_v50_group_0_24_diff;
	u32 dfd_v50_group_0_25_diff;
	u32 dfd_v50_group_0_26_diff;
	u32 dfd_v50_group_0_27_diff;
	u32 dfd_v50_group_0_28_diff;
	u32 dfd_v50_group_0_29_diff;
	u32 dfd_v50_group_0_30_diff;
	u32 dfd_v50_group_0_31_diff;
	u32 dfd_v50_chain_group_3_0_info;
	u32 dfd_v50_chain_group_7_4_info;
	u32 dfd_v50_chain_group_11_8_info;
	u32 dfd_v50_chain_group_15_12_info;
	u32 dfd_v50_chain_group_19_16_info;
	u32 dfd_v50_chain_group_23_20_info;
	u32 dfd_v50_chain_group_27_24_info;
	u32 dfd_v50_chain_group_31_28_info;
	u32 dfd_v50_chain_group_35_32_info;
	u32 dfd_v50_chain_group_39_36_info;
	u32 dfd_v50_chain_group_43_40_info;
	u32 dfd_v50_chain_group_47_44_info;
	u32 dfd_v50_chain_group_51_48_info;
	u32 dfd_v50_chain_group_55_52_info;
	u32 dfd_v50_chain_group_59_56_info;
	u32 dfd_v50_chain_group_63_60_info;
	u32 dfd_v50_chain_group_67_64_info;
	u32 dfd_v50_chain_group_71_68_info;
	u32 dfd_v50_chain_group_75_72_info;
	u32 dfd_v50_chain_group_79_76_info;
	u32 dfd_v50_chain_group_83_80_info;
	u32 dfd_v50_chain_group_87_84_info;
	u32 dfd_v50_chain_group_91_88_info;
	u32 dfd_v50_chain_group_95_92_info;
	u32 dfd_v50_chain_group_99_96_info;
	u32 dfd_v50_chain_group_103_100_info;
	u32 dfd_v50_chain_group_107_104_info;
	u32 dfd_v50_chain_group_111_108_info;
	u32 dfd_v50_chain_group_115_112_info;
	u32 dfd_v50_chain_group_119_116_info;
	u32 dfd_v50_chain_group_123_120_info;
	u32 dfd_v50_chain_group_127_124_info;
	u32 dfd_test_si_2;
	u32 dfd_test_si_3;
	u32 dfd_test_so;
	u32 dfd_bus_halt_time;
	u32 dfd_read_addr;
	u32 dfd_v50_clk_stop_time;
	u32 dfd_v50_group_0_32_diff;
	u32 dfd_v50_group_0_33_diff;
	u32 dfd_v50_group_0_34_diff;
	u32 dfd_v50_group_0_35_diff;
	u32 dfd_v50_group_0_36_diff;
	u32 dfd_v50_group_0_37_diff;
	u32 dfd_v50_group_0_38_diff;
	u32 dfd_v50_group_0_39_diff;
	u32 dfd_v50_group_0_40_diff;
	u32 dfd_v50_group_0_41_diff;
	u32 dfd_v50_group_0_42_diff;
	u32 dfd_v50_group_0_43_diff;
	u32 dfd_v50_group_0_44_diff;
	u32 dfd_v50_group_0_45_diff;
	u32 dfd_v50_group_0_46_diff;
	u32 dfd_v50_group_0_47_diff;
	u32 dfd_v50_group_0_48_diff;
	u32 dfd_v50_group_0_49_diff;
	u32 dfd_v50_group_0_50_diff;
	u32 dfd_v50_group_0_51_diff;
	u32 dfd_v50_group_0_52_diff;
	u32 dfd_v50_group_0_53_diff;
	u32 dfd_v50_group_0_54_diff;
	u32 dfd_v50_group_0_55_diff;
	u32 dfd_v50_group_0_56_diff;
	u32 dfd_v50_group_0_57_diff;
	u32 dfd_v50_group_0_58_diff;
	u32 dfd_v50_group_0_59_diff;
	u32 dfd_v50_group_0_60_diff;
	u32 dfd_v50_group_0_61_diff;
	u32 dfd_v50_group_0_62_diff;
	u32 dfd_v50_group_0_63_diff;
	u32 rsv_62b0[20];
	u32 dfd_v50_spare;
	u32 rsv_6304[1843];
	u32 mcusys_reserved_reg4;
	u32 mcusys_reserved_reg4_rd;
	u32 rsv_7fd8[2];
	u32 mcusys_reserved_reg0;
	u32 mcusys_reserved_reg1;
	u32 mcusys_reserved_reg2;
	u32 mcusys_reserved_reg3;
	u32 mcusys_reserved_reg0_rd;
	u32 mcusys_reserved_reg1_rd;
	u32 mcusys_reserved_reg2_rd;
	u32 mcusys_reserved_reg3_rd;
};

check_member(mt8195_mcucfg_regs, cpu_plldiv_cfg0, 0x22a0);
check_member(mt8195_mcucfg_regs, bus_plldiv_cfg, 0x22e0);

static struct mt8195_mcucfg_regs *const mt8195_mcucfg = (void *)MCUCFG_BASE;

#endif  /* SOC_MEDIATEK_MT8195_MCUCFG_H */