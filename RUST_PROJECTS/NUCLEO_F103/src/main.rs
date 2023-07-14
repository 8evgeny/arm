#![deny(unsafe_code)]
#![no_std]
#![no_main]

use panic_halt as _;

use nb::block;

use cortex_m_rt::entry;
use embedded_hal::digital::v2::OutputPin;
use stm32f1xx_hal::{pac, prelude::*, timer::Timer};

// Определяем входную функцию.
#[entry]
fn main() -> ! {
    // Получаем управление над аппаратными средствами
    let cp = cortex_m::Peripherals::take().unwrap();
    let dp = pac::Peripherals::take().unwrap();
    let mut flash = dp.FLASH.constrain();
    let mut rcc = dp.RCC.constrain();

    let clocks = rcc.cfgr.freeze(&mut flash.acr);
    // let mut gpiob = dp.GPIOB.split(&mut rcc.apb2);
    let mut gpioa = dp.GPIOA.split(&mut rcc.apb2);

    // Конфигурируем пин a5 как двухтактный выход.
    // Регистр "crh" передаётся в функцию для настройки порта.
    // Для пинов 0-7, необходимо передавать регистр "crl".
    // let mut led = gpiob.pb12.into_push_pull_output(&mut gpiob.crh);
    let mut led1 = gpioa.pa5.into_push_pull_output(&mut gpioa.crl);
    // Конфигурируем системный таймер на запуск обновления каждую секунду.
    let mut timer = Timer::syst(cp.SYST, &clocks).start_count_down(5.hz());

    // Ждём пока таймер запустит обновление
    // и изменит состояние светодиода.
    loop {
        block!(timer.wait()).unwrap();
        led1.set_high().unwrap();
        block!(timer.wait()).unwrap();
        led1.set_low().unwrap();
    }
}
