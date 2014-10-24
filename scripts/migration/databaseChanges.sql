alter table issues add reportedByPerson_id int unsigned after workOrder_id;
alter table workOrders add completedByPerson_id int unsigned after meter_id;
