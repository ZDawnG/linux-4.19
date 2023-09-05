/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _RAID0_H
#define _RAID0_H

#include <linux/workqueue.h>
#include <linux/mempool.h>

struct strip_zone {
	sector_t zone_end;	/* Start of the next zone (in sectors) */
	sector_t dev_start;	/* Zone offset in real dev (in sectors) */
	int	 nb_dev;	/* # of devices attached to the zone */
};

struct r0conf {
	struct strip_zone	*strip_zone;
	struct md_rdev		**devlist; /* lists of rdevs, pointed to
					    * by strip_zone->dev */
	int			nr_strip_zones;
	struct workqueue_struct *read_workqueue;
	struct workqueue_struct *write_workqueue;
	mempool_t *read_work_pool;
	mempool_t *write_work_pool;
	u64 max_sector;
	u64 enable_time_stats;
	u64 tmp_period_time;
	u64 total_period_time;
	u64 write_period_time;
	u64 reads_period_time;
	long long int io_count;
	long long int page_count;
	long long int io_count_free;
	long long int page_count_free;
};

struct r5_check_io {
	struct r0conf* conf;
	struct md_rdev *dev;
	struct page *page;
	struct page *bio_page;
	sector_t sector;
	int is_remote;
	u64 entry_offset;
};

struct r5_check_work {
	struct work_struct worker;
	struct r5_check_io *io;
};

#endif
