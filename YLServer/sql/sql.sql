CREATE TABLE `yl_user` (
  `user_id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT '用户id',
  `user_account` varchar(12) NOT NULL COMMENT '用户账号',
  `user_password` varchar(256) NOT NULL COMMENT '密码',
  `user_nickname` varchar(32) CHARACTER SET utf8mb4 NOT NULL COMMENT '昵称',
  `user_phone` varchar(11) DEFAULT NULL COMMENT '手机号',
  `user_sex` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '1男2女0未知',
  `user_email` varchar(64) DEFAULT NULL COMMENT '邮箱',
  `user_header` varchar(255) CHARACTER SET utf8mb4 NOT NULL COMMENT '头像地址',
  `user_created` int(11) unsigned NOT NULL COMMENT '信息更新时间',
  `user_updated` int(11) unsigned NOT NULL COMMENT '账号创建时间',
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;



CREATE TABLE `yl_friend` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL COMMENT '用户id',
  `friend_id` int(11) unsigned NOT NULL COMMENT '好友id',
  `group_id` int(11) unsigned NOT NULL COMMENT '好友所在组的组id',
  `created` int(11) unsigned NOT NULL COMMENT '创建时间',
  `status` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '1添加成功 0待确认',
  `friend_remark` varchar(100) CHARACTER SET utf8mb4 DEFAULT NULL COMMENT '好友备注',
  PRIMARY KEY (`id`),
  KEY `yl_friend_user_id_IDX` (`user_id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8s

CREATE TABLE `yl_friend_group` (
  `group_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) unsigned NOT NULL COMMENT '用户id, 如果为0，则表示全部用户共享',
  `group_name` varchar(64) NOT NULL COMMENT '分组名称',
  PRIMARY KEY (`group_id`),
  KEY `yl_friend_group_user_id_IDX` (`user_id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8


CREATE TABLE `yl_session` (
  `session_id` int(11) unsigned NOT NULL COMMENT 'session_id',
  `user_id` int(11) unsigned NOT NULL,
  `other_id` int(11) unsigned NOT NULL COMMENT '可以是好友ID也可以是群组ID',
  `session_type` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '会话类型： 1 用户  2群组',
  `sesionn_top` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '0不置顶 1置顶',
  `session_status` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '用户：0正常1删除 群组0正常1删除',
  `session_created` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `session_updated` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '更新时间',
  PRIMARY KEY (`session_id`),
  KEY `yl_session_user_id_IDX` (`user_id`,`other_id`,`session_type`) USING BTREE,
  KEY `yl_session_other_id_IDX` (`other_id`,`user_id`,`session_status`,`session_updated`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='最近会话'


CREATE TABLE `yl_message` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `relate_id` int(11) unsigned NOT NULL COMMENT '关联yl_friend 中的id',
  `sender_id` int(11) unsigned NOT NULL COMMENT '发送者ID',
  `receiver_id` int(11) unsigned NOT NULL COMMENT '接受者id',
  `message_id` int(11) unsigned NOT NULL COMMENT '消息ID',
  `message_content` varchar(4096) CHARACTER SET utf8mb4 DEFAULT NULL COMMENT '消息内容',
  `message_type` tinyint(1) unsigned NOT NULL DEFAULT '1' COMMENT '消息类型',
  `message_status` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '0正常 1删除',
  `message_updated` int(11) unsigned NOT NULL COMMENT '更新时间，，删除的时间',
  `message_created` int(11) unsigned NOT NULL COMMENT '创建时间 (用户发送的时间)',
  PRIMARY KEY (`id`),
  KEY `yl_message_relate_id_IDX` (`relate_id`,`message_status`,`message_created`) USING BTREE,
  KEY `relateId_status_created_IDX` (`relate_id`,`message_status`,`message_id`,`message_created`) USING BTREE,
  KEY `yl_message_sender_id_IDX` (`sender_id`,`receiver_id`,`message_status`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='消息表'
