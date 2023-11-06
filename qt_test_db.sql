-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 06, 2023 at 01:04 PM
-- Server version: 10.4.18-MariaDB
-- PHP Version: 8.0.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `qt_test_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `cars`
--

CREATE TABLE `cars` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `full_name` varchar(250) NOT NULL,
  `gender` enum('male','female','','') NOT NULL,
  `year` int(11) NOT NULL,
  `name` varchar(250) NOT NULL,
  `color` varchar(15) NOT NULL,
  `place` varchar(250) NOT NULL,
  `national_code` varchar(15) NOT NULL,
  `address` varchar(250) NOT NULL,
  `passenger_count` int(11) NOT NULL,
  `health` int(11) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `cars`
--

INSERT INTO `cars` (`id`, `user_id`, `full_name`, `gender`, `year`, `name`, `color`, `place`, `national_code`, `address`, `passenger_count`, `health`, `created_at`) VALUES
(1, 1, 'سارا محمدی', 'male', 0, 'پژو', '#ff557d', 'اصفهان', '2', 'آدرس تست', 3, 4, '2023-11-03 16:44:19'),
(2, 1, 'مهدی احمدی', 'male', 0, 'سمند', '#ff0509', 'فیروز کوه', '1234', 'اصفهان اصفهان', 4, 80, '2023-11-03 16:50:02'),
(3, 2, 'سارا محمدی', 'female', 0, 'سمند', '#ffffff', 'گلپایگان', '1234', 'شیراز', 6, 4, '2023-11-03 16:52:21'),
(4, 2, 'احمد احمدی', 'male', 0, 'پراید', '#69ff66', 'گلپایگان', '4545', 'تهران', 4, 4, '2023-11-03 16:53:13'),
(5, 3, 'سارا محمدی', 'male', 0, 'پژو', '#ff4769', 'گلپایگان', '4545', 'اصفهان اصفهان', 3, 4, '2023-11-03 16:56:17'),
(6, 3, 'مهدی احمدی', 'male', 0, 'پژو', 'none', 'گلپایگان', '45', 'آدرس', 3, 5, '2023-11-03 16:58:22');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `full_name` varchar(128) NOT NULL,
  `username` varchar(128) NOT NULL,
  `password` varchar(512) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `full_name`, `username`, `password`, `created_at`) VALUES
(1, 'test', 'user', '202cb962ac59075b964b07152d234b70', '2023-11-02 15:42:15'),
(2, 'مهدی مرادی', 'mahdi_moradi', '202cb962ac59075b964b07152d234b70', '2023-11-02 16:19:09');

-- --------------------------------------------------------

--
-- Table structure for table `user_access_tokens`
--

CREATE TABLE `user_access_tokens` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `token` varchar(128) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `user_access_tokens`
--

INSERT INTO `user_access_tokens` (`id`, `user_id`, `token`, `created_at`) VALUES
(16, 2, '9319f2e692fae3780bf4a100b3fdbd18', '2023-11-03 14:59:18'),
(17, 2, 'bd0b3cdb7dfe0f34b08e13c90e66cb06', '2023-11-03 15:02:01'),
(18, 2, '68a7660c1a07b55e9d264b5153e6a74a', '2023-11-03 15:03:16'),
(26, 2, '5fac08091946e0ed8e5360350d428c97', '2023-11-03 16:19:26'),
(27, 2, '86c258de9b2998d48651185ae3e6c403', '2023-11-03 16:23:37'),
(28, 2, '33f5af6550acee62445eeb98fb524d0e', '2023-11-03 16:25:26'),
(29, 2, '19cf20a433d45ba1419e929d2b02e013', '2023-11-03 16:27:05'),
(30, 2, 'f157ffe84a14e65b7e81a1a00d69440d', '2023-11-03 16:31:29'),
(31, 2, '9e368ffda05b39bf75cc6d1fae95d288', '2023-11-03 16:33:22'),
(32, 2, '05edab5de0178cf519cbc17f1444cc6c', '2023-11-03 16:34:20'),
(33, 2, '4b00b70d0272ce0f4ead5899307efe0a', '2023-11-03 16:35:46'),
(34, 2, 'ee79de25017637297a51f7586b26c4d4', '2023-11-03 16:38:55'),
(35, 2, '4bb1db67ed9b2a8b710748e980f2d3e0', '2023-11-03 16:40:37'),
(36, 2, '5cac99a78ad679e364d577bf128edf5d', '2023-11-03 16:42:31'),
(37, 2, 'fd2264049456ed9e89624a3a6e1e0196', '2023-11-03 16:44:06'),
(38, 2, 'b001f167c56705cf3a857ccadadee20e', '2023-11-03 16:49:30'),
(39, 2, '9828982c18f203b0e7734a7a4baf0a30', '2023-11-03 16:51:58'),
(40, 2, 'a8bb21dc932d55329104d14e64337a6e', '2023-11-03 16:52:53'),
(41, 2, 'f9095990eb53dec875c3bbb80e6ef71b', '2023-11-03 16:56:00'),
(42, 2, '580d344c62d26ecae38729da913afda1', '2023-11-03 16:58:10'),
(53, 2, '3a9a0346a9325578796a70a1292a3649', '2023-11-03 18:52:21'),
(55, 2, 'ce24a4ca946cc14eb82dd0e57df8720b', '2023-11-03 18:55:39'),
(62, 2, '37a5688e741eb3bcf169fd9c98d450f0', '2023-11-04 08:48:54'),
(63, 2, '07e874780b0fc061ca490753d093ea79', '2023-11-04 08:49:46');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `cars`
--
ALTER TABLE `cars`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `user_access_tokens`
--
ALTER TABLE `user_access_tokens`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `cars`
--
ALTER TABLE `cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `user_access_tokens`
--
ALTER TABLE `user_access_tokens`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=66;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
