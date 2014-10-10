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
    name varchar(32) not null
);

create table activity (
    id   int unsigned not null primary key auto_increment,
    meter_id int unsigned not null,
    reportedDate datetime,
    resolvedDate datetime,
    comments text,
    foreign key (meter_id) references meters(id)
);

create table activity_issueTypes (
    activity_id  int unsigned not null,
    issueType_id int unsigned not null,
    primary key (activity_id, issueType_id),
    foreign key (activity_id)  references activity  (id),
    foreign key (issueType_id) references issueTypes(id)
);

