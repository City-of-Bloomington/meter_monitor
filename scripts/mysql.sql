-- @copyright 2006-2012 City of Bloomington, Indiana
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

create table issueTypes (
    id int unsigned not null primary key auto_increment,
    name varchar(32) not null
);

create table issues (
    id   int unsigned not null primary key auto_increment,
    zone int unsigned,
    meter varchar(24) not null,
    issueType_id int unsigned,
    reportedDate datetime,
    resolvedDate datetime,
    comments text,
    foreign key (issueType_id) references issueTypes(id)
);
