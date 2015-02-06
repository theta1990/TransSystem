#include "../../exec/PhyPlanFactory.h"
#include "../../trans/MyServer.h"
#include "../common/test.h"
#include "../../storage/TableMgr.h"
#include "../../storage/SchemaMgr.h"
#include "../../common/serialization.h"

using namespace expdb;

int createWareHouseTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "w_id");
	desc.addRowType(STR, "w_name", 11);
	desc.addRowType(STR, "w_street_1", 21);
	desc.addRowType(STR, "w_street_2", 21);
	desc.addRowType(STR, "w_city", 21);
	desc.addRowType(STR,"w_state", 3);
	desc.addRowType(STR, "w_zip", 11);


	priIdx[0] = 0;
	desc.setPriIdx(priIdx, 1);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("warehouse", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createDistrictTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(SMALLINT, "d_id");
	desc.addRowType(MIDINT, "d_w_id");
	desc.addRowType(STR, "d_name", 11);
	desc.addRowType(STR, "d_street_1", 21);
	desc.addRowType(STR, "d_street_2", 21);
	desc.addRowType(STR, "d_city", 21);
	desc.addRowType(STR, "d_state", 3);
	desc.addRowType(STR, "d_zip", 10);

//	desc.addRowType(DEC, "d_tax", 4, 4, true);
	desc.addRowType(DOUBLE, "d_tax");
//	desc.addRowType(DEC, "d_ytd", 12, 2, true);
	desc.addRowType(DOUBLE, "d_ytd");
	desc.addRowType(MIDINT, "d_next_o_id");

	priIdx[0] = 0;
	priIdx[1] = 1;
	desc.setPriIdx(priIdx, 2);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("district", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createCustomerTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "c_id");
	desc.addRowType(SMALLINT, "c_d_id");
	desc.addRowType(MIDINT, "c_w_id");

	desc.addRowType(STR, "c_first", 17);
	desc.addRowType(STR, "c_middle", 3);
	desc.addRowType(STR, "c_last", 17);
	desc.addRowType(STR, "c_street_1", 21);
	desc.addRowType(STR, "c_street_2", 21);
	desc.addRowType(STR, "c_city", 21);
	desc.addRowType(STR, "c_state", 2);
	desc.addRowType(STR, "c_zip", 10);
	desc.addRowType(STR, "c_phone", 17);

//	desc.addRowType(DATE, "C_SINCE");
	desc.addRowType(BIGINT, "C_SINCE");
	desc.addRowType(STR, "c_credit", 3);
//	desc.addRowType(DEC, "c_credit_lim", 12, 2, true);
	desc.addRowType(DOUBLE, "c_credit_lim");
//	desc.addRowType(DEC, "c_discount", 4, 4, true);
	desc.addRowType(DOUBLE, "c_discount");
//	desc.addRowType(DEC, "c_balance", 12, 2, true);
	desc.addRowType(DOUBLE, "c_balance");
//	desc.addRowType(DEC, "c_ytd_payment", 12, 2, true);
	desc.addRowType(DOUBLE, "c_ytd_payment");
//	desc.addRowType(DEC, "c_payment_cnt", 4, 0, false);
	desc.addRowType(DOUBLE, "c_payment_cnt");
//	desc.addRowType(DEC, "c_delivery_cnt", 4, 0, false);
	desc.addRowType(DOUBLE, "c_delivery_cnt");
	desc.addRowType(STR, "c_data", 500);	//variable size;

	priIdx[0] = 2;
	priIdx[1] = 1;
	priIdx[2] = 0;
	desc.setPriIdx(priIdx, 3);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("customer", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

/**
 * 是不是要有一个自增主键？
 *
 */
int createHistoryTable(){

	//TODO 增加自增主键
	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
//	int32_t priIdx[8];

	desc.addRowType(MIDINT, "h_c_id");
	desc.addRowType(SMALLINT, "h_c_d_id");
	desc.addRowType(MIDINT, "h_c_w_id");
	desc.addRowType(SMALLINT, "h_d_id");
	desc.addRowType(MIDINT, "h_w_id");
//	desc.addRowType(DATE, "h_date");
	desc.addRowType(BIGINT, "h_date");
//	desc.addRowType(DEC, "h_amount", 6, 2, true);
	desc.addRowType(DOUBLE, "h_amount");
	desc.addRowType(STR, "h_data", 25);

	// (h_c_w_id, h_c_d_id, h_c_id) foreign key,
	// refer to (c_w_id, c_d_id, c_id)

	// (h_w_id, h_d_id) foreign key
	// refer to (d_w_id, d_id)

	if (SUCCESS != SchemaMgr::getInstance()->addTable("history", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createNewOrderTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "no_o_id");
	desc.addRowType(SMALLINT, "no_d_id");
	desc.addRowType(MIDINT, "no_w_id");

	priIdx[0] = 2;
	priIdx[1] = 1;
	priIdx[2] = 3;
	desc.setPriIdx(priIdx, 3);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("neworder", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}


int createOrder(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "o_id");
	desc.addRowType(SMALLINT, "o_d_id");
	desc.addRowType(MIDINT, "o_w_id");
	desc.addRowType(MIDINT, "o_c_id");
//	desc.addRowType(DATE, "o_entry_d");
	desc.addRowType(BIGINT, "o_entry_d");
	desc.addRowType(SMALLINT, "o_carrier_id");
//	desc.addRowType(DEC, "o_ol_cnt", 2, 0, false);
	desc.addRowType(DOUBLE, "o_ol_cnt");
//	desc.addRowType(DEC, "o_all_local", 1, 0, false);
	desc.addRowType(DOUBLE, "o_all_local");

	priIdx[0] = 2;
	priIdx[1] = 1;
	priIdx[2] = 0;
	desc.setPriIdx(priIdx, 3);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("order", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createOrderLine(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "ol_o_id");
	desc.addRowType(SMALLINT, "ol_d_id");
	desc.addRowType(MIDINT, "ol_w_id");
	desc.addRowType(SMALLINT, "ol_number");
	desc.addRowType(MIDINT, "ol_i_id");
	desc.addRowType(MIDINT, "ol_supply_w_id");
//	desc.addRowType(DATE, "ol_delivery_d");
	desc.addRowType(BIGINT, "ol_delivery_d");
//	desc.addRowType(DEC, "ol_quantity", 2, 0, false);
	desc.addRowType(DOUBLE, "ol_quantity");
//	desc.addRowType(DEC, "ol_amount", 6, 2, false);
	desc.addRowType(DOUBLE, "ol_amount");
	desc.addRowType(STR, "ol_dist_info", 25);

	priIdx[3] = 2;
	priIdx[2] = 1;
	priIdx[1] = 0;
	priIdx[0] = 3;
	desc.setPriIdx(priIdx, 4);
	if (SUCCESS != SchemaMgr::getInstance()->addTable("orderline", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createItemTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "i_id");
	desc.addRowType(MIDINT, "i_im_id");
	desc.addRowType(STR, "i_name", 25);
//	desc.addRowType(DEC, "i_price", 5, 2, false);
	desc.addRowType(DOUBLE, "i_price");
	desc.addRowType(STR, "i_data", 51);

	priIdx[0] = 0;
	desc.setPriIdx(priIdx, 1);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("item", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}

int createStockTable(){

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	int32_t priIdx[8];

	desc.addRowType(MIDINT, "s_i_id");
	desc.addRowType(MIDINT, "s_w_id");
//	desc.addRowType(DEC, "s_quantity", 4, 0, true);
	desc.addRowType(DOUBLE, "s_quantity");
	desc.addRowType(STR, "s_dist_01", 25);
	desc.addRowType(STR, "s_dist_02", 25);
	desc.addRowType(STR, "s_dist_03", 25);
	desc.addRowType(STR, "s_dist_04", 25);
	desc.addRowType(STR, "s_dist_05", 25);
	desc.addRowType(STR, "s_dist_06", 25);
	desc.addRowType(STR, "s_dist_07", 25);
	desc.addRowType(STR, "s_dist_08", 25);
	desc.addRowType(STR, "s_dist_09", 25);
	desc.addRowType(STR, "s_dist_10", 25);

//	desc.addRowType(DEC, "s_ytd", 8,0, false);
	desc.addRowType(DOUBLE, "s_ytd");
//	desc.addRowType(DEC, "s_order_cnt", 4, 0, false);
	desc.addRowType(DOUBLE, "s_order_cnt");
//	desc.addRowType(DEC, "s_remote_cnt", 4, 0, false);
	desc.addRowType(DOUBLE, "s_remote_cnt");
	desc.addRowType(STR, "s_data", 51);

	priIdx[0] = 1;
	priIdx[1] = 0;
	desc.setPriIdx(priIdx, 2);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("stock", &desc, storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
	return 0;
}


int neword(){




	return 0;
}




