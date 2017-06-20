CREATE TABLE IF NOT EXISTS ft_table(
	id int PRIMARY KEY  NOT NULL AUTO_INCREMENT,
	login VARCHAR(20) NOT NULL DEFAULT 'toto',
	groupe ENUM('staff', 'student', 'other') NOT NULL,
	date_de_creation DATE NOT NULL
);
