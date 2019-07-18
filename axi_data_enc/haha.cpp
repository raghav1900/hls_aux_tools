//#BEGIN#
// Bitmap indicating presence of optional PDUsBit 0: pdschPtrs  -IndicatesPTRS included (FR2) Bit 1:cbgRetxCtrl (Present when CBG based retransmit is used)All other bits reserved
pdsch_pdu_t.pduBitmap = data_in.tdata.range(15,0);
// The RNTI used for identifying the UE when receiving the PDUValue: 1 -> 65535
pdsch_pdu_t.RNTI = data_in.tdata.range(31,16);
// PDU index incremented for each PDSCH PDU sent in TX control message. This is used to associate control information to data and is reset every slot. Value:0 ->65535
pdsch_pdu_t.pduIndex = data_in.tdata.range(47,32);
// Bandwidthpart size[TS38.213 sec12]. Number of contiguous PRBs allocated to the BWPValue: 1->275
pdsch_pdu_t.BWPSize = data_in.tdata.range(63,48);
//#END#
//#BEGIN#
// bandwidth part start RB indexfrom reference CRB [TS38.213 sec 12]Value: 0->274
pdsch_pdu_t.BWPStart = data_in.tdata.range(15,0);
// subcarrierSpacing [TS38.211 sec 4.2]Value:0->4
pdsch_pdu_t.SubcarrierSpacing = data_in.tdata.range(23,16);
// Cyclic prefix type[TS38.211 sec 4.2]0: Normal; 1: Extended
pdsch_pdu_t.CyclicPrefix = data_in.tdata.range(31,24);
// Number ofcodewordsfor this RNTI (UE)Value: 1 -> 2
pdsch_pdu_t.NrOfCodewords = data_in.tdata.range(39,32);
// Target coding rate [TS38.212sec5.4.2.1and 38.214 sec 5.1.3.1]. This is the number of information bits per 1024 coded bits expressed in 0.1 bit units
pdsch_pdu_t.targetCodeRate = data_in.tdata.range(55,40);
// QAM modulation[TS38.212sec5.4.2.1and 38.214 sec 5.1.3.1] Value: 2,4,6,8
pdsch_pdu_t.qamModOrder = data_in.tdata.range(63,56);
//#END#
//#BEGIN#
// MCS index[TS38.214, sec 5.1.3.1], should match value sent in DCIValue : 0->31
pdsch_pdu_t.mcsIndex = data_in.tdata.range(7,0);
// MCS-Table-PDSCH[TS38.214, sec 5.1.3.1]0: notqam2561: qam2562: qam64LowSE
pdsch_pdu_t.mcsTable = data_in.tdata.range(15,8);
// Redundancy versionindex [TS38.212, Table 5.4.2.1-2 and 38.214, Table 5.1.2.1-2], should match value sent in DCIValue : 0->3
pdsch_pdu_t.rvIndex = data_in.tdata.range(23,16);
// Transmit block size (in bytes)[TS38.214 sec 5.1.3.2]Value: 0->65535
pdsch_pdu_t.TBSize = data_in.tdata.range(55,24);
//#END#
//#BEGIN#
// dataScramblingIdentityPdsch [TS38.211, sec 7.3.1.1]It equals the higher-layer parameter Data-scrambling-Identity if configured and the RNTI equals the C-RNTI, otherwise L2 needs to set it to physical cell id.Value: 0->65535
pdsch_pdu_t.dataScramblingId = data_in.tdata.range(-1,-16);
// Number of layers [TS38.211, sec 7.3.1.3]Value : 1->8
pdsch_pdu_t.nrOfLayers = data_in.tdata.range(7,0);
// PDSCH transmission schemes [TS38.214, sec 5.1.1]0: Up to 8 transmission layers
pdsch_pdu_t.transmissionScheme = data_in.tdata.range(15,8);
// Reference point forPDSCH DMRS "k" -used for tone mapping [TS38.211, sec 7.4.1.1.2]Resource block bundles [TS38.211, sec 7.3.1.6]Value: 0 -> 1If 0, the 0 reference point for PDSCH DMRSis at Point A [TS38.211 sec 4.4.4.2]. Resource block bundles generated per sub-bullets 2 and 3 in [TS38.211, sec 7.3.1.6]. For sub-bullet 2, the start of bandwidth part must be set to the start of actual bandwidth part +NstartCORESETand the bandwidth of the bandwidth part must be set to the bandwidth of the initial bandwidth part.If 1, the DMRS reference point is at the lowest VRB/PRB of the allocation. Resource block bundles generated per sub-bullets 1 [TS38.211, sec7.3.1.6]
pdsch_pdu_t.refPoint = data_in.tdata.range(23,16);
// DMRS symbol positions [TS38.211, sec7.4.1.1.2andTables7.4.1.1.2-3 and 7.4.1.1.2-4]Bitmapoccupying the14 LSBswith: bit 0: first symboland for each bit0: no DMRS1: DMRS
pdsch_pdu_t.dlDmrsSymbPos = data_in.tdata.range(39,24);
// DL DMRS config type[TS38.211, sec 7.4.1.1.2]0: type 11: type2
pdsch_pdu_t.dmrsConfigType = data_in.tdata.range(47,40);
//#END#
//#BEGIN#
// DL-DMRS-Scrambling-ID [TS38.211, sec 7.4.1.1.2 ]If provided by the higher-layer and the PDSCH is scheduled by PDCCH with CRC scrambled by C-RNTI or CS-RNTI, otherwise, L2 should set thisto physical cell id.Value: 0->65535
pdsch_pdu_t.dlDmrsScramblingId = data_in.tdata.range(-1,-16);
// DMRS sequence initialization [TS38.211, sec 7.4.1.1.2]. Should match what is sent in DCI 1_1, otherwise set to 0.Value : 0->1
pdsch_pdu_t.SCID = data_in.tdata.range(7,0);
// Number of DM-RS CDM groups without data [TS38.212 sec 7.3.1.2.2] [TS38.214 Table 4.1-1]it determines the ratio of PDSCH EPRE to DM-RS EPRE.Value: 1->3
pdsch_pdu_t.numDmrsCdmGrpsNoData = data_in.tdata.range(15,8);
// DMRS ports.[TS38.212 7.3.1.2.2] provides description between DCI 1-1 content and DMRS ports.Bitmap occupying the 11 LSBswith: bit 0: antenna port 1000bit 11: antenna port 1011and for each bit0: DMRS port not used1: DMRS port used
pdsch_pdu_t.dmrsPorts = data_in.tdata.range(31,16);
// Resource Allocation Type [TS38.214, sec 5.1.2.2]0: Type 01: Type 1
pdsch_pdu_t.resourceAlloc = data_in.tdata.range(39,32);
// For resource alloc type 0.TS 38.212 V15.0.x, 7.3.1.2.2 bitmap of RBs, 273 rounded up to multiple of 32. This bitmap is in units of VRBs. LSB of byte 0 of the bitmap represents the first RB of the bwp
//pdsch_pdu_t.rbBitmap[36] = data_in.tdata.range(39,40);
// For resource allocationtype 1. [TS38.214, sec 5.1.2.2.2]The starting resource block within the BWP for this PDSCH.Value: 0->274
pdsch_pdu_t.rbStart = data_in.tdata.range(55,40);
//#END#
//#BEGIN#
// For resource allocation type 1. [TS38.214, sec 5.1.2.2.2]The number of resource block within for this PDSCH Value: 1->275
pdsch_pdu_t.rbSize = data_in.tdata.range(15,0);
// VRB-to-PRB-mapping[TS38.211, sec 7.3.1.6]0: non-interleaved 1: interleaved with RB size 22: Interleaved with RB size 4
pdsch_pdu_t.VRBtoPRBMapping = data_in.tdata.range(23,16);
// Start symbol index of PDSCH mappingfrom the start of the slot, S. [TS38.214, Table 5.1.2.1-1]Value: 0->13
pdsch_pdu_t.StartSymbolIndex = data_in.tdata.range(31,24);
// PDSCH duration in symbols, L [TS38.214, Table 5.1.2.1-1]Value: 1->14
pdsch_pdu_t.NrOfSymbols = data_in.tdata.range(39,32);
// PT-RS antenna ports [TS38.214, sec 5.1.6.3] [TS38.211, table 7.4.1.2.2-1]Bitmap occupying the 6LSBswith: bit 0: antenna port 1000bit 5: antenna port 1005and for each bit0: PTRSport not used1: PTRSport used
pdsch_pdu_t.PTRSPortIndex = data_in.tdata.range(47,40);
// PT-RS time density[TS38.214, table 5.1.6.3-1]0: 11: 22: 4
pdsch_pdu_t.PTRSTimeDensity = data_in.tdata.range(55,48);
// PT-RS frequency density[TS38.214, table 5.1.6.3-2]0: 21: 4
pdsch_pdu_t.PTRSFreqDensity = data_in.tdata.range(63,56);
//#END#
//#BEGIN#
// PT-RS resource elementoffset[TS38.211, table 7.4.1.2.2-1]Value: 0->3
pdsch_pdu_t.PTRSReOffset = data_in.tdata.range(7,0);
// PT-RS-to-PDSCH EPRE ratio [TS38.214, table 4.1-2]Value :0->3
pdsch_pdu_t.nEpreRatioOfPDSCHToPTRS = data_in.tdata.range(15,8);
// See Table 3-43 for structure, NOT IMPLEMENTED
//pdsch_pdu_t.Precoding and Beamforming = data_in.tdata.range(15,16);
// Ratio of PDSCH EPRE to NZP CSI-RSEPRE [TS38.214, sec 5.2.2.3.1]Value :0->23representing -8 to 15 dB in 1dB steps
pdsch_pdu_t.powerControlOffset = data_in.tdata.range(23,16);
// Ratio of SSB/PBCH block EPRE to NZP CSI-RS EPRES [TS38.214, sec 5.2.2.3.1] Values:0: -3dB,1: 0dB,2: 3dB,3: 6dB
pdsch_pdu_t.powerControlOffsetSS = data_in.tdata.range(31,24);
// Indicates whether last CB is present in the CBG retransmission 0: CBG retransmission does not include last CB 1: CBG retransmission includes last CB If CBG Re-Tx includes last CB, L1 will add the TB CRC to the last CB in the payload before it is read into the LDPC HW unit
pdsch_pdu_t.IsLastCbPresent = data_in.tdata.range(39,32);
// Indicates whether TB CRC is part of data payload or control message 0: TB CRC is part of data payload 1: TB CRC is part of control message
pdsch_pdu_t.isInlineTbCrc = data_in.tdata.range(47,40);
// TB CRC: to be used in the last CB, applicable only if last CB is present
pdsch_pdu_t.dlTbCrc = data_in.tdata.range(55,48);
// 0
//0.0 = data_in.tdata.range(55,56);
// Base Graph Value
pdsch_c_pdu_t.bg = data_in.tdata.range(57,56);
//#END#
//#BEGIN#
// Number of codeblocks
pdsch_c_pdu_t.num_cb = data_in.tdata.range(-5,-12);
// nan
//pdsch_c_pdu_t.CRC Polynomial = data_in.tdata.range(3,-4);
// number of message bits in the code block after CRC
pdsch_c_pdu_t.k = data_in.tdata.range(17,4);
// nan
pdsch_c_pdu_t.Z_ind = data_in.tdata.range(23,18);
// nan
pdsch_c_pdu_t.G = data_in.tdata.range(55,24);
//#END#
//#BEGIN#
// RM block output, first series
pdsch_c_pdu_t.E_0 = data_in.tdata.range(9,-4);
// Second Series
pdsch_c_pdu_t.E_1 = data_in.tdata.range(23,10);
// Index where the series shifts
pdsch_c_pdu_t.E_shift = data_in.tdata.range(31,24);
//#END#
Total Number of AXI Messages = 10
/*
{'axi_w': 64, 'mode': 1, 'filename': ['/home/jaswanthi/Downloads/phy_param_master - struct_defs.csv'], 'prev_index': 52, 'offset': -30.0, 'cur_mesg': 8, 'index': 52}
*/
