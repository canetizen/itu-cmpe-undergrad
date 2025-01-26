create database UNIVERSITY;

use university;

create table DEPARTMENT
 (dept_id    varchar(10),
  dept_name  varchar(50), 
  building   varchar(50), 
  primary key (dept_id)
 );

create table COURSE
 (course_id     varchar(10), 
  course_title  varchar(50), 
  dept_id       varchar(10),
  credits       smallint CHECK (credits >= 0),
  primary key (course_id),
  foreign key (dept_id) references department (dept_id)
     on delete set null
 );

create table INSTRUCTOR
 (instructor_id     varchar(10), 
  instructor_name   varchar(50) not null, 
  dept_id           varchar(10), 
  primary key (instructor_id),
  foreign key (dept_id) references department (dept_id)
    on delete set null
 );

create table TEACHES
 (CRN int UNIQUE,    -- CRN : Course Registration Number
  instructor_id    varchar(10), 
  course_id        varchar(10),
  year_semester    varchar(15),
  primary key (CRN, instructor_id, course_id),
  foreign key (course_id) references course (course_id)
     on delete cascade,
  foreign key (instructor_id) references instructor (instructor_id)
     on delete cascade
 );
create table STUDENT
 (student_id      varchar(10), 
  student_name    varchar(50) not null, 
  dept_id         varchar(10), 
  total_credits   smallint CHECK (total_credits >= 0),
  primary key (student_id),
  foreign key (dept_id) references department (dept_id)
     on delete set null
 );

create table TAKES
 (student_id   varchar(10), 
  CRN          int,
  grade        varchar(2),
  primary key (student_id, CRN),
  foreign key (CRN) references teaches (CRN)
     on delete cascade,
  foreign key (student_id) references student (student_id)
     on delete cascade
 );
