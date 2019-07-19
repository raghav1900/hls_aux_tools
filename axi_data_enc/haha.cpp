//#BEGIN#
// nan
l1_ctrl_inst_t.n_users = data_in.tdata.range(7,0);
// nan
l1_ctrl_inst_t.param_calc_tb_dirt_bit = data_in.tdata.range(8,8);
// nan
l1_ctrl_inst_t.param_calc_rm_dirt_bit = data_in.tdata.range(9,9);
// nan
l1_ctrl_inst_t.max_cb_sched = data_in.tdata.range(18,10);
// nan
l1_ctrl_inst_t.cur_phy_sched = data_in.tdata.range(27,19);
// nan
l1_ctrl_inst_t.cw_phy_index_sched[512] = data_in.tdata.range(35,28);
