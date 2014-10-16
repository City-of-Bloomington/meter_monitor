-- @copyright 2014 City of Bloomington, Indiana
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
-- @author Cliff Ingham <inghamn@bloomington.in.gov>
create table people (
	id int unsigned not null primary key auto_increment,
	firstname varchar(128) not null,
	lastname varchar(128) not null,
	email varchar(255) not null,
	username varchar(40) unique,
	password varchar(40),
	authenticationMethod varchar(40),
	role varchar(30)
);

create table meters (
    id int unsigned not null primary key auto_increment,
    name varchar(12) not null unique,
    zone tinyint unsigned not null
);

create table issueTypes (
    id int unsigned not null primary key auto_increment,
    name varchar(32) not null,
    description varchar(255)
);

create table issues (
    id           int unsigned not null primary key auto_increment,
    meter_id     int unsigned not null,
    issueType_id int unsigned not null,
    workOrder_id int unsigned not null,
    reportedDate date not null,
    comments text,
    foreign key (meter_id)     references meters    (id),
    foreign key (issueType_id) references issueTypes(id)
);

create table issue_issueTypes (
    issue_id     int unsigned not null,
    issueType_id int unsigned not null,
    primary key (issue_id, issueType_id),
    foreign key (issue_id)     references issues    (id),
    foreign key (issueType_id) references issueTypes(id)
);

create table workTypes (
    id int unsigned not null primary key auto_increment,
    name varchar(32) not null,
    description varchar(255)
);

create table workOrders (
    id       int unsigned not null primary key auto_increment,
    meter_id int unsigned not null,
    dateCompleted date    not null,
    comments text,
    foreign key (meter_id) references meters(id)
);

create table workOrder_workTypes (
    workOrder_id int unsigned not null,
    workType_id  int unsigned not null,
    primary key (workOrder_id,  workType_id),
    foreign key (workOrder_id) references workOrders(id),
    foreign key (workType_id)  references workTypes (id)
);
