create table packet( 
	packet_id INT UNSIGNED NOT NULL AUTO_INCREMENT, 
	session_id int not null, 
	start_time int not null, 
	end_time int not null, 
	next_hop varchar(256) null, 
	source int not null, 
	sink int not null, 
	PRIMARY KEY(packet_id) 
);

create table nodeInfo(
	nodeId int not null,  
	numbers int not null default 0,
	time int not null,
	primary KEY(nodeId, time)
);
