input: wid, did, cid, oOlCnt, oAllLocal

gettimeofday(datetime);

integer discount, last, credit, tax;

select c_dis, c_last, c_credit, w_tax
	into discount, last, credit, tax
	from customer, warehouse
	where w_id = wid and c_w_id = wid and c_d_id = did and c_id = cid;


integer dNextOrderId, dTax;
select d_next_o_id, d_tax into dNextOrderId, dTax
	from district
	where d_id = did and d_w_id = wid;

update district set d_next_o_id = dNextOrderId + 1 
	where d_id = did and d_w_id = wid;

orderId = dNextOrderId;

insert into orders(o_id, o_d_id, o_w_id, o_c_id, o_entry_d, o_ol_cnt, o_all_local)
  	values(orderId, did, wid, cid, datetime, oOlCnt, oAllLocal);

insert into neworder(no_o_id, no_d_id, no_w_id) 
  	values(orderId, did, wid);

for(olNumber = 1; olNumber <= oOlCnt; olNumber++){

  olSupplyWid = atol(supware[olNumber-1]);
  if( olSupplyWid != wid ) oAllLocal = 0;
  
  ol_i_id = atol( itemid[olNumber-1] );
  ol_quantity = aotl( qty[olNumber -1] );

  select i_price, i_name, i_data
    into itemPrice, itemName, itemData
    from item
    where i_id = ol_i_id;

  price[olNumber-1] = itemPrice;
  strncpy(iname[olNumber-1], itemName, 24);

  select s_quantity, s_data, s_dist01, s_dist_02, s_dist_03, s_dist_04, s_dist_05, s_dist_06, s_dist_07, s_dist_08, s_dist_09, s_dist_10
    into squantity, sdata, sdist01, sdist02, sdist03, sdist04, sdist05, sdist06, sdist07, sdist08, sdist09, sdist10
    from stock
    where s_i_id = ol_i_id and s_w_id = ol_suppy_w_id;











}
