/*
 Navicat Premium Data Transfer

 Source Server         : game
 Source Server Type    : MySQL
 Source Server Version : 50720
 Source Host           : 47.93.235.6:3306
 Source Schema         : chivalrousman

 Target Server Type    : MySQL
 Target Server Version : 50720
 File Encoding         : 65001

 Date: 28/04/2019 21:07:34
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for User
-- ----------------------------
DROP TABLE IF EXISTS `User`;
CREATE TABLE `User`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `address` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `psw` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `email` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for backpack
-- ----------------------------
DROP TABLE IF EXISTS `backpack`;
CREATE TABLE `backpack`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `thingname` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `thingtype` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `thingnums` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `thinggrade` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for equipmentinfo
-- ----------------------------
DROP TABLE IF EXISTS `equipmentinfo`;
CREATE TABLE `equipmentinfo`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `equipmentname` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `grade` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `type` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for friend
-- ----------------------------
DROP TABLE IF EXISTS `friend`;
CREATE TABLE `friend`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `friendpname` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `friendrname` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `friendrtype` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `friendgrade` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  PRIMARY KEY (`playername`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for magicweapon
-- ----------------------------
DROP TABLE IF EXISTS `magicweapon`;
CREATE TABLE `magicweapon`  (
  `id` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `attr` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `attrvalue` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for player
-- ----------------------------
DROP TABLE IF EXISTS `player`;
CREATE TABLE `player`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `playerpsw` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `nums` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`playername`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playergongfa
-- ----------------------------
DROP TABLE IF EXISTS `playergongfa`;
CREATE TABLE `playergongfa`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `name` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playerinfo
-- ----------------------------
DROP TABLE IF EXISTS `playerinfo`;
CREATE TABLE `playerinfo`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `roletype` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `glod` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `grade` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `blood` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `mana` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `attack` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `defense` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `speed` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `exp` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `maxexp` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `destx` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `desty` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `level` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `sect` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `gongfa` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `jingjie` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  PRIMARY KEY (`rolename`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playerjingjie
-- ----------------------------
DROP TABLE IF EXISTS `playerjingjie`;
CREATE TABLE `playerjingjie`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `jingjie` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `curexp` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '',
  `exp` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playermw
-- ----------------------------
DROP TABLE IF EXISTS `playermw`;
CREATE TABLE `playermw`  (
  `playername` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `rolename` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mw_name` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `grade` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `curexp` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `exp` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `is_in_battle` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for skillinfo
-- ----------------------------
DROP TABLE IF EXISTS `skillinfo`;
CREATE TABLE `skillinfo`  (
  `playername` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `rolename` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `skillname` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `skillgrade` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '0'
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
