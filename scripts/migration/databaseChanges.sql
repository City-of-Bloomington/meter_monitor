alter table activity modify reportedDate date not null;
alter table activity modify resolvedDate date;

rename table activity to issues;
rename table activity_issueTypes to issue_issueTypes;

alter table issue_issueTypes drop foreign key issue_issueTypes_ibfk_1;
alter table issue_issueTypes change activity_id issue_id int unsigned not null;
alter table issue_issueTypes add foreign key (issue_id) references issues(id);
