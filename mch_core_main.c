/*************************************************************************/ /*
 avb-mch

 Copyright (C) 2016 Renesas Electronics Corporation

 License        Dual MIT/GPLv2

 The contents of this file are subject to the MIT license as set out below.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 Alternatively, the contents of this file may be used under the terms of
 the GNU General Public License Version 2 ("GPL") in which case the provisions
 of GPL are applicable instead of those above.

 If you wish to allow use of your version of this file only under the terms of
 GPL, and not to allow others to use your version of this file under the terms
 of the MIT license, indicate your decision by deleting the provisions above
 and replace them with the notice and other provisions required by GPL as set
 out in the file called "GPL-COPYING" included in this distribution. If you do
 not delete the provisions above, a recipient may use your version of this file
 under the terms of either the MIT license or GPL.

 This License is also included in this distribution in the file called
 "MIT-COPYING".

 EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
 PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


 GPLv2:
 If you wish to use this file under the terms of GPL, following terms are
 effective.

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; version 2 of the License.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/ /*************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/vmalloc.h>

struct mch_private {
	/* MCH Control */
	struct device dev;
};

struct mch_private *mch_priv_ptr;

#define PPB_SCALE (1000000000ULL)

/*
 * public functions
 */
int mch_open(int *dev_id)
{
	if (!dev_id)
		return -1;

	*dev_id = 0;

	return 0;
}
EXPORT_SYMBOL(mch_open);

int mch_close(int dev_id)
{
	return 0;
}
EXPORT_SYMBOL(mch_close);

int mch_send_timestamps(int dev_id, int time_rate_ns,
			int master_count,
			unsigned int master_timestamps[],
			int device_count,
			unsigned int device_timestamps[])
{
	return 0;
}
EXPORT_SYMBOL(mch_send_timestamps);

int mch_get_recovery_value(int dev_id, int *value)
{
	if (!value)
		return -1;

	*value = PPB_SCALE;

	return 0;
}
EXPORT_SYMBOL(mch_get_recovery_value);

/*
 * module init/cleanup
 */
static int __init mch_module_init(void)
{
	int err;
	struct mch_private *mch_priv;

	pr_info("init: start\n");

	err = -ENOMEM;
	mch_priv = vzalloc(sizeof(*mch_priv));
	if (unlikely(!mch_priv))
		goto no_memory;

	mch_priv_ptr = mch_priv;

	pr_info("init: success\n");

	return 0;

no_memory:
	mch_priv_ptr = NULL;

	pr_info("init: failed\n");

	return err;
}

static void __exit mch_module_exit(void)
{
	struct mch_private *mch_priv = mch_priv_ptr;

	pr_info("cleanup: start\n");

	mch_priv_ptr = NULL;
	vfree(mch_priv);

	pr_info("cleanup: end\n");
}

module_init(mch_module_init);
module_exit(mch_module_exit);

MODULE_AUTHOR("Renesas Electronics Corporation");
MODULE_DESCRIPTION("Renesas Media Clock recovery Handler");
MODULE_LICENSE("Dual MIT/GPL");
