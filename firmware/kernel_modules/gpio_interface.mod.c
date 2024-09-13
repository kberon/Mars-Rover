#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x122c3a7e, "_printk" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0xb43f9365, "ktime_get" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x3086c22a, "gpio_to_desc" },
	{ 0x5dd551e6, "gpiod_direction_input" },
	{ 0xed2b3346, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x3a3b9f5d, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7BCBA113616EB264B5D348A");
